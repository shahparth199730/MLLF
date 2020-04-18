#include"scheduler.h"

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
        //*(executionTimeArr+i*2+1)=1*taskSet[i].c;
    }
}

void ResetNextJob(struct task *taskSet,float *execArr,int nextTaskID)
{
    (*(execArr+(nextTaskID-1)*2))+=taskSet[nextTaskID-1].p;           
    *(execArr+(nextTaskID-1)*2+1)=GetRandomNumber()*taskSet[nextTaskID-1].c;
    //*(execArr+(nextTaskID-1)*2+1)=1*taskSet[nextTaskID-1].c;
}