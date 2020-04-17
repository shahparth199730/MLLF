#include"scheduler.h"

struct task* AllocateTaskSet(struct task* taskSet)
{
  taskSet=(struct task*)malloc(sizeof(struct task));
  return taskSet;
}

struct task* ReAllocateTaskSet(struct task* taskSet,int noOfTasks)
{
  taskSet=(struct task*) realloc(taskSet,noOfTasks*sizeof(struct task)+sizeof(struct task));
  return taskSet;
}

struct task* InitializeTask(struct task* taskSet,char* line,int count)
{ 
    //read each line and set the parameters for the taskset
    char* token=strtok(line,",");
    char *param[4];
    int i=0;
    while(token!=NULL)
    {
        param[i++]=token;
        token=strtok(NULL,",");   
    }
    taskSet[count].id=count+1;
    taskSet[count].phase=atof(param[0]);
    taskSet[count].p=atof(param[1]);
    taskSet[count].c=atof(param[2]);
    taskSet[count].d=atof(param[3]);
    return taskSet;
}

void PrintTaskSet(struct task *taskSet,int noOfTasks)
{
  int i;
  printf("*****************************************TASKSET****************************************\n");
  for(i=0;i<noOfTasks;i++)
  {
      printf("ID:%d\tPhase:%.2f\tPeriod:%.2f\tExecution Time:%.2f\tRelative Deadline: %.2f\n",
      taskSet[i].id,taskSet[i].phase,taskSet[i].p,taskSet[i].c,taskSet[i].d);
  }
}