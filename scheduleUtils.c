#include"scheduler.h"


struct job* FindFeasibleSchedule(struct task* taskSet,float end,int noOfTasks,int *jobCount)
{
    float *execArr,current=0.0,*cur,*latencyOfActiveTasks;
    cur=&current;
    struct job *schedule=NULL;
    struct task *nextTask,*previousTask;
    int *activeTaskCount,count=0,i,*activeTasks,*noOfJobsInSchedule,jobCo=0,*noOfOverheads,overheadCount=0;
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
        FindNextTaskToBeScheduled(activeTasks,*activeTaskCount,cur,taskSet,execArr);
        current+=end;
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

struct task* FindNextTaskToBeScheduled(int *activeTasks,int activeTaskCount,float *current,struct task *taskSet,float *execArr)
{
    //find latency of all the tasks available
    float *laxityArr=NULL;
    struct task *nextTask=(struct task *)malloc(sizeof(struct task));
    int i;
    laxityArr=FindLaxityOfAvailableTasks(activeTasks,activeTaskCount,*current,execArr);
    for(i=0;i<activeTaskCount;i++)
    {
        printf("Task ID:%d Laxity:%.2f\n",activeTasks[i],laxityArr[i]);
    }
    return nextTask;
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