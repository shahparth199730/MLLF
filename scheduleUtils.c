#include"scheduler.h"


struct job* FindFeasibleSchedule(struct task* taskSet,float end,int noOfTasks,int *jobCount)
{
    float *execArr,current=0.0,*cur,*latencyOfActiveTasks,duration,*minTaskLaxity,minLaxity;
    minTaskLaxity=&minLaxity;
    cur=&current;
    struct job *schedule=NULL;
    int *activeTaskCount,count=0,i,*activeTasks,*noOfJobsInSchedule,jobCo=0,*noOfOverheads,overheadCount=0,prevTaskID=0,nextTaskID;
    noOfOverheads=&overheadCount;
    activeTaskCount=&count;
    noOfJobsInSchedule=&jobCo;
    execArr=CreateExecutionTimeArr(noOfTasks);
    InitializeExecutionTimeArr(execArr,taskSet,noOfTasks);
    //initially find currently active tasks at 
    while(current<end)
    {
        //add an overhead job whenever trying to make any decision
        schedule=AddOverheadToSchedule(schedule,noOfJobsInSchedule,cur,noOfOverheads,true);
        //among the available tasks, look for the tasks available
        activeTasks=FindCurrentlyActiveTasks(execArr,noOfTasks,*cur,activeTaskCount);
        nextTaskID=FindNextTaskToBeScheduled(activeTasks,*activeTaskCount,cur,taskSet,execArr,prevTaskID,minTaskLaxity);
        //TODO: look for how much period the task can be scheduled
        duration=FindJobDuration(nextTaskID,taskSet,execArr,*cur,noOfTasks,end,*minTaskLaxity);
        //TODO: for period, look when the next event occurs 1. new job come 2. TQ expires 3. job finishes(find the min among these)
        //TODO: create a job for that much period
        //TODO: add that job to the schedule
        //TODO: increment the current by that time duration
        //TODO: reduce the remaining exec time of the task
        //TODO: if the task get finished, reassign the exec Array
        //TODO: if the newly allocated task is not equal to prev and prev!=0, add premption ovehead

        current+=end;
        //TODO: set prev task id nd next task id
        //TODO: add to the schedule
        //TODO: set next to prev
       // nextTask=FindNextTaskToBeScheduled(activeTasks,activeTaskCount,current,taskSet,execArr);
        //previousTask=nextTask;
    }
    
    return schedule;
}


int* FindCurrentlyActiveTasks(float* executionTimeArr,int noOfTasks,float currentTime,int *activeTaskCount)
{
    //TODO: push the ids of the currently active tasks to the output
    //active tasks are those who have been released and not finished yet
    int i,*activeTasks=NULL;
    for(i=0;i<noOfTasks;i++)
    {
        if(*(executionTimeArr+i*2)<=currentTime )
        {
            if((*(executionTimeArr+i*2+1))>0)
            {
                activeTasks=(int *)realloc(activeTasks,*activeTaskCount*sizeof(int)+sizeof(int));
                activeTasks[(*activeTaskCount)]=i+1;
                (*activeTaskCount)++;
            }
        }
    }
    return activeTasks;
}

float* CreateExecutionTimeArr(int noOfTasks)
{
    float* executionTimeArr=(float *) malloc(noOfTasks*2*sizeof(float));
    return executionTimeArr;
}


void InitializeExecutionTimeArr(float* executionTimeArr,struct task* taskSet,int noOfTasks)
{
    //for each task in the taskSet, initialize the corresponding actual execution time
    //index 0 in executionTimeArr refer to task 1, 1 to task 2 and so on
    int i;
    for(i=0;i<noOfTasks;i++)
    {
        //set phase for the first index in the row and actual execution time for the next
        *(executionTimeArr+i*2)=taskSet[i].phase;           
        *(executionTimeArr+i*2+1)=GetRandomNumber()*taskSet[i].c;
        printf("Task ID:%d Phase:%.2f Exec Time:%.2f\n",i+1,*(executionTimeArr+i*2),*(executionTimeArr+i*2+1));
    }
}


float GetRandomNumber()
{
    //everytime generates a different random number within the given range
    float randomNumber;
    randomNumber=((rand()%5)+6)/10.0;
    return randomNumber;
}

struct job* AddOverheadToSchedule(struct job* schedule,int *noOfJobsInSchedule,float *current,int *noOfOverheads,bool isDesionOverhead)
{
    //create a job with overhead
    schedule=AddOverheadJob(schedule,*noOfJobsInSchedule,*current,*noOfOverheads,isDesionOverhead);
    (*noOfJobsInSchedule)++;
    (*current)+=0.1;
    (*noOfOverheads)+=1;
    return schedule;
}



struct job* AddOverheadJob(struct job* schedule,int noOfJobsInSchedule,float current,int noOfOverheads,bool isDesionOverhead)
{
    schedule=(struct job*)realloc(schedule,(noOfJobsInSchedule*sizeof(struct job))+sizeof(struct job));
    //assign the job for decision overhead
    schedule[noOfJobsInSchedule].startTime=current;
    //add  0.1 and 0.2 for premption overhead
    schedule[noOfJobsInSchedule].endTime=current+=(isDesionOverhead?0.1:0.2);
    schedule[noOfJobsInSchedule].associatedTask=NULL;
    schedule[noOfJobsInSchedule].absoluteDeadline=0.0;
    schedule[noOfJobsInSchedule].id[0]=0;
    schedule[noOfJobsInSchedule].id[1]=0;
    schedule[noOfJobsInSchedule].id[2]=noOfOverheads;
    schedule[noOfJobsInSchedule].isOverhead=true;
    schedule[noOfJobsInSchedule].jobType=(isDesionOverhead?contextOverhead:preemptionOverhead);
    return schedule;
}

int FindNextTaskToBeScheduled(int *activeTasks,int activeTaskCount,float *current,struct task *taskSet,float *execArr,int prevTask,float *minTaskLatency)
{
    //find latency of all the tasks available
    float *laxityArr=NULL,minLaxity;
    int nextTaskID;
    int *minLaxityTaskArr=NULL,minLaxityTaskCount=0,i;
    laxityArr=FindLaxityOfAvailableTasks(activeTasks,activeTaskCount,*current,execArr);
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

float* FindLaxityOfAvailableTasks(int *activeTasks,int activeTaskCount,float current,float *execArr)
{
    int i;
    float *activeTasksLaxity=(float*)malloc(activeTaskCount*sizeof(float));   

    for(i=0;i<activeTaskCount;i++)
    {
        //find latency for each active task
        float laxity;
        laxity=FindLaxity(activeTasks[i],execArr,current);
        activeTasksLaxity[i]=laxity;
    }
    return activeTasksLaxity;
}

float FindLaxity(int taskID,float *execArr,float current)
{
    //laxity=absoluteDeadline+(currentTime+remainingExecTime);
    //execArr stores the absolute deadline and remaining execution time
    //for task id i, execArr row i-1 has these values
    float laxity;
    laxity=*(execArr+(taskID-1)*2+1)-(current+*(execArr+(taskID-1)*2));
    return laxity;
}

float FindMinLaxity(float *activeTasksLaxity,int activeTaskCount)
{
    int i;
    float minLaxity=activeTasksLaxity[0];
    for(i=1;i<activeTaskCount;i++)
    {
        if(activeTasksLaxity[i]<minLaxity)
            minLaxity=activeTasksLaxity[i];
    }
    return minLaxity;
}

int BreakTie(int *minLaxityTaskArr,int minLaxityTaskCount,float *execArr,int prevTask)
{
    int i,*minExecutionTimeTasks=NULL,minExeTasksCount=0,minLaxityTask=0,minIDTask;
    float minExeTime;
    //continue the currently executing task if minLaxityTaskArr contains cur task
    if(prevTask!=0)
    {
        for(i=0;i<minLaxityTaskCount;i++)
        {
            if(minLaxityTaskArr[i]==prevTask)
            {
                return minLaxityTaskArr[i];
            }
        }
    }
    minExeTime=*(execArr+(minLaxityTaskArr[minLaxityTask]-1)*2+1);
    //else, check for the one with min remaining execution time and schedule it
    //find the min execution time among the set of tasks
    for(i=1;i<minLaxityTaskCount;i++)
    {
        //check if the remaining time of the task is less than one with already assigned
        if(*(execArr+(minLaxityTaskArr[i]-1)*2+1)<minExeTime)
        {
            minExeTime=*(execArr+(minLaxityTaskArr[i]-1)*2+1);
            minLaxityTask=minLaxityTaskArr[i];
        }
    }
    //check for the tasks present with min laxities with min execution time
    for(i=0;i<minLaxityTaskCount;i++)
    {
        //if execution time of a task is equal to min exec time, add it to the array
        if(*(execArr+(minLaxityTaskArr[i]-1)*2+1)==minExeTime)
        {
            minExecutionTimeTasks=(int *)realloc(minExecutionTimeTasks,minExeTasksCount*sizeof(int)+sizeof(int));
            minExecutionTimeTasks[minExeTasksCount]=minLaxityTaskArr[i];
            minExeTasksCount++;
        }
    }
    
    //if multiple with min execution times
    if(minExeTasksCount>1)
    {
        minIDTask=minExecutionTimeTasks[0];
        //find the one with min id
        for(i=1;i<minExeTasksCount;i++)
        {
            if(minExecutionTimeTasks[i]<minIDTask)
                minIDTask=minExecutionTimeTasks[i];
        }
    }
    else
        return minExecutionTimeTasks[0];
}

float FindJobDuration(int nextTaskID,struct task *taskSet,float *execArr,float current,int noOfTasks,float end,float curMinLaxity)
{
    float duration,nextTaskArrival,currentTaskOver,nearestEvent,tq,tqOverEvent;
    int tmin;
    /*3 events until next job
        1. new job comes
        2. current task over
        3. TQ expires
    */
    //1.new job comes
    nextTaskArrival=FindNextTaskArrival(taskSet,execArr,current,noOfTasks,end);
    currentTaskOver= current+*(execArr+(nextTaskID-1)*2+1);
    nearestEvent=(nextTaskArrival!=0&&nextTaskArrival<currentTaskOver?nextTaskArrival:currentTaskOver);
    //Time Quantum
    tmin=FindTMIN(taskSet,noOfTasks,nextTaskID,current,curMinLaxity,execArr);
    if(tmin!=0)
    {
        //time quantum=deadline of the min-current laxity
        tq=*(execArr+2*(tmin-1))-curMinLaxity;
    }
    tqOverEvent=current+tq;
    nearestEvent=(tqOverEvent<nearestEvent?nearestEvent:tqOverEvent);
    //TODO: verify if next task arrival is not 0
    //Duration=nextEventTime-current;
    duration=nearestEvent-current;
    return duration;
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

int FindTMIN(struct task *taskSet,int noOfTasks,int nextTaskID,float current,float curMinLatency,float *execArr)
{
    //TMin is the one which has earliest deadline among all the tasks and latency greater than the current task latency
    int i,j=0,tmin=0;
    float curTaskDeadline=*(execArr+(nextTaskID-1)*2);
    for(i=0;i<noOfTasks;i++)
    {
        if(i!=nextTaskID)
        {
            //deadline must be greater than current and nearest i.e.., nearer than current task's deadline
            if(*(execArr+i*2)<curTaskDeadline && (j==0 || *(execArr+2*i)<*(execArr+2*(tmin-1))))
            {
                tmin=i+1;
                j++;
            }

        }
    }
    return tmin;
}