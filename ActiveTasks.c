#include"scheduler.h"

int* FindCurrentlyActiveTasks(float* executionTimeArr,int noOfTasks,float currentTime,int *activeTaskCount)
{
    //TODO: push the ids of the currently active tasks to the output
    //active tasks are those who have been released and not finished yet
    int i,*activeTasks=NULL;
    for(i=0;i<noOfTasks;i++)
    {
        //tasks released on or before the current task and has remaining execution time
        //and rem exec time 0.1 or greater
        if(*(executionTimeArr+i*2)<=currentTime && *(executionTimeArr+i*2+1)>=0.1)
        {
            activeTasks=(int *)realloc(activeTasks,*activeTaskCount*sizeof(int)+sizeof(int));
            activeTasks[(*activeTaskCount)]=i+1;
            (*activeTaskCount)++;
        }
    }
    return activeTasks;
}


