#include"scheduler.h"

float* FindLaxityOfAvailableTasks(int *activeTasks,struct task *taskSet,int activeTaskCount,float current,float *execArr)
{
    int i;
    float *activeTasksLaxity=(float*)malloc(activeTaskCount*sizeof(float));   

    for(i=0;i<activeTaskCount;i++)
    {
        //find latency for each active task
        float laxity;
       
        laxity=FindLaxity(taskSet,activeTasks[i],execArr,current);
        printf("Task ID:%d Laxity:%.2f\n",activeTasks[i],laxity);
        activeTasksLaxity[i]=laxity;
    }
    return activeTasksLaxity;
}

float FindLaxity(struct task *taskSet,int taskID,float *execArr,float current)
{
    //laxity=absoluteDeadline+(currentTime+remainingExecTime);
    //execArr stores the absolute deadline and remaining execution time
    //for task id i, execArr row i-1 has these values
    float laxity;
    laxity=((*(execArr+(taskID-1)*2))+taskSet[taskID-1].p)-(current+*(execArr+(taskID-1)*2+1));
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