#include"scheduler.h"


struct job* FindFeasibleSchedule(struct task* taskSet,float end,int noOfTasks,int *jobCount)
{
    float *execArr,current=0.0,*cur,*latencyOfActiveTasks,duration,*minTaskLaxity,minLaxity;
    minTaskLaxity=&minLaxity;
    cur=&current;
    struct job *schedule=NULL;
    bool isPrevJobFinished;
    int *latestSubJobIdArr=(int *)malloc(noOfTasks*sizeof(int));
    int *activeTaskCount,count=0,i,*activeTasks,*noOfJobsInSchedule,jobCo=0,*noOfOverheads,overheadCount=0,prevTaskID=0,nextTaskID;
    //initilize the task id array
    //index 0 is for task 1, i.e.., i for task id i+1
    for(i=0;i<noOfTasks;i++)
        latestSubJobIdArr[i]=1;
    noOfOverheads=&overheadCount;
    activeTaskCount=&count;
    noOfJobsInSchedule=&jobCo;
    execArr=CreateExecutionTimeArr(noOfTasks);
    InitializeExecutionTimeArr(execArr,taskSet,noOfTasks);
    //initially find currently active tasks at 
    int j=0;
    while((*cur)<end)
    {
        //add an overhead job whenever trying to make any decision
        //TODO: uncomment next line
        //schedule=AddOverheadToSchedule(schedule,noOfJobsInSchedule,cur,noOfOverheads,true);
        //among the available tasks, look for the tasks available
        //TODO: how do we ensure the granularity of 0.1
        *activeTaskCount=0;
        activeTasks=FindCurrentlyActiveTasks(execArr,noOfTasks,*cur,activeTaskCount);
        printf("List of active tasks whose count is %d\n",*activeTaskCount);
        //TODO: if active tasks is null, wait till the next job arrives
        for(i=0;i<*activeTaskCount;i++)
        {
            printf("TASK ID: %d Arrival Time: %.2f Rem Exe Time:%.2f\n",
            activeTasks[i],*(execArr+(activeTasks[i]-1)*2),*(execArr+(activeTasks[i]-1)*2+1));
        }
        j++;
        if(j>=15)
        break;
        if((*activeTaskCount)==0)
        {
            printf("pppppppppp cur is %.2f",*cur);
            float nextJobArrival= getNextJobArrivalTime(execArr,*cur,noOfTasks);
            printf("next job arrival is at %.2f\n",nextJobArrival);
            *cur+=(nextJobArrival-*cur);
            printf("cur hogya %.2f\n",*cur);
            continue;
            //TODO: skip decision making overhead in this case  
            //TODO add duration to cur;
        }
        nextTaskID=FindNextTaskToBeScheduled(activeTasks,*activeTaskCount,cur,taskSet,execArr,prevTaskID,minTaskLaxity);
        //means no next task present, so simply exit
        printf("Next task hega %d\n",nextTaskID);

        if(nextTaskID==0)
            break;
        //check if job prempted i.e.., job was asked to leave but not complete yet
        if(prevTaskID!=0 && nextTaskID!=prevTaskID && !isPrevJobFinished)
        {
            printf("premption overhead\n");
            //TODO:uncomment next line
            //schedule=AddOverheadToSchedule(schedule,noOfJobsInSchedule,cur,noOfOverheads,false);
        }

        //for duration, look when the next event occurs 1. new job come 2. TQ expires 3. job finishes(find the min among these)
        duration=FindJobDuration(nextTaskID,taskSet,execArr,*cur,noOfTasks,end,*minTaskLaxity);
        //TODO: create a job for that much period and add it to the schedule
        printf("DURATION NIKLI %.2f\n",duration);
        schedule=AddJobToSchedule(schedule,taskSet,nextTaskID,duration,execArr,cur,noOfJobsInSchedule,latestSubJobIdArr[nextTaskID-1]);
        printf("cur: %.2f and Job id %d %d\n",*cur,schedule[*noOfJobsInSchedule-1].id[0],schedule[*noOfJobsInSchedule-1].id[1]);
        //duration==remaining execution time for that task,job is done
        if(*(execArr+(nextTaskID-1)*2+1)>=duration)
        {
            //if job finished,reinitialize the jobid for that task,else update the latestJobID for the task executed
            isPrevJobFinished=true;
            //reset next job, and set the sub job array count to 1
            ResetNextJob(taskSet,execArr,nextTaskID);
            latestSubJobIdArr[nextTaskID-1]=1;
        }
        else
        {
            //reduce the duration from remaining exec time
            *(execArr+(nextTaskID-1)*2+1)-=duration;
            isPrevJobFinished=false;
        }
        
        //TODO: also set isPrevJobFinished
        //TODO: change the random
        prevTaskID=nextTaskID;
    }
    
    return schedule;
}












