#include"scheduler.h"

bool CheckTaskSetFeasibility(struct task *taskSet,int noOfTasks)
{
  int i;
  float utilization=0;
  for(int i=0;i<noOfTasks;i++){
      utilization+=(taskSet[i].c/taskSet[i].p);
  }
  return (utilization<=1);
}