#include"scheduler.h"


struct job* FindFeasibleSchedule(struct task* taskSet,int noOfTasks,int *jobCount)
{
    float *execArr;
    struct job *schedule;
    int *activeTaskCount,count=0,i,*activeTasks;
    activeTaskCount=&count;
    execArr=CreateExecutionTimeArr(noOfTasks);
    InitializeExecutionTimeArr(execArr,taskSet,noOfTasks);
    activeTasks=FindCurrentlyActiveTasks(execArr,noOfTasks,0.0,activeTaskCount);
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
    }
}


float GetRandomNumber()
{
    //everytime generates a different random number within the given range
    float randomNumber;
    randomNumber=((rand()%5)+6)/10.0;
    return randomNumber;
}
