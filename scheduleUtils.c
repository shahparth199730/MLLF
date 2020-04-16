#include"scheduler.h"


struct job* FindFeasibleSchedule(struct task* taskSet,int noOfTasks,int *jobCount)
{
    float *execArr;
    struct job *schedule;
    execArr=CreateExecutionTimeArr(noOfTasks);
    InitializeExecutionTimeArr(execArr,taskSet,noOfTasks);
    return schedule;
}


int* FindCurrentlyActiveTasks(struct task* taskSet,int noOfTasks,float currentTime)
{
    //TODO: push the ids of the currently active tasks to the output
}

float* CreateExecutionTimeArr(int noOfTasks)
{
    /* Why noOfTasks*2 has been done? Please clarify it to me. i am not getting it.*/
    float* executionTimeArr=(float *) malloc(noOfTasks*2);
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
        *(executionTimeArr+i)=taskSet[i].phase;
        float random=GetRandomNumber();        
        *(executionTimeArr+i+1)=(random)*taskSet[i].c;
    }
    
}


float GetRandomNumber()
{
    //everytime generates a different random number within the given range
    float randomNumber;
    randomNumber=((rand()%5)+6)/10.0;
    return randomNumber;
}
