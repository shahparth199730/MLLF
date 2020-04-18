#include"scheduler.h"

int FindNextTaskToBeScheduled(int *activeTasks,int activeTaskCount,float current,struct task *taskSet,float *execArr,int prevTask,float *minTaskLatency)
{
    //find latency of all the tasks available
    float *laxityArr=NULL,minLaxity;
    int nextTaskID=0;
    int *minLaxityTaskArr=NULL,minLaxityTaskCount=0,i;
    laxityArr=FindLaxityOfAvailableTasks(activeTasks,taskSet, activeTaskCount,current,execArr);
    minLaxity=FindMinLaxity(laxityArr,activeTaskCount);
    *minTaskLatency=minLaxity;
    for(i=0;i<activeTaskCount;i++)
    {
        if(laxityArr[i]==minLaxity)
        {
            minLaxityTaskArr=(int*)realloc(minLaxityTaskArr,minLaxityTaskCount*sizeof(int)+sizeof(int));
            //adding the task id to the array
            minLaxityTaskArr[minLaxityTaskCount]=activeTasks[i];
            minLaxityTaskCount++;
        }
    }
    //break the tie among tasks if multiple tasks with min laxity
    if(minLaxityTaskCount>1)
        nextTaskID=BreakTie(minLaxityTaskArr,minLaxityTaskCount,execArr,prevTask);
    else
        nextTaskID=minLaxityTaskArr[0];
    return nextTaskID;
}


float FindNextTaskArrival(struct task *taskSet,float *execArr,float current,int noOfTasks,float end)
{
    //find when is the next job coming for each task, the min among them is the next job arrival
    float *nextJobArrival=(float *)malloc(noOfTasks*sizeof(float)),period,jobArrivalTime,nearestJobArrivalTime=INT_MAX;
    int i,noOfJobs,j;
    //initialize the array
    for(i=0;i<noOfTasks;i++)
        nextJobArrival[i]=INT_MAX;
    
    //for each task, see at what times job comes
    for(i=0;i<noOfTasks;i++)
    {
        period=taskSet[i].p;
        noOfJobs=floor(end/period);
        for(j=0;j<noOfJobs;j++)
        {
            jobArrivalTime=j*period;
            //start from the beginning and look first job which arrives after just after the current.
            if(jobArrivalTime>current)
            {
                nextJobArrival[i]=jobArrivalTime;
                break;
            }
        }
    }
    
    for(i=0;i<noOfTasks;i++)
    {
        if(nextJobArrival[i]!=INT_MAX && nextJobArrival[i]<nearestJobArrivalTime)
            nearestJobArrivalTime=nextJobArrival[i];
    }

    free(nextJobArrival);
    //int_max only is no remaining job till end for any task
    return (nearestJobArrivalTime==INT_MAX?0.0:nearestJobArrivalTime);
}

float getNextJobArrivalTime(float *execArr,float current,int noOfTasks)
{
    int i,p=0;
    float nextJobArrival=0;
    //next job arrival is at
    //1. after the current
    //2. earliert after current
    for(i=0;i<noOfTasks;i++)
    {
        if((*(execArr+i*2))>current && (p==0||(*(execArr+i*2))<nextJobArrival))
        {
            nextJobArrival=(*(execArr+i*2));
            p++;
        }
            
    }
    return nextJobArrival;
}