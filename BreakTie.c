#include"scheduler.h"

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