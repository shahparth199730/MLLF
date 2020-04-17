#include"scheduler.h"

float Inphase(struct task *taskSet, int count,float hp){
  int *x=(int *)malloc(count*sizeof(int));
  float max=0.0;
  int id=-1;
  int flag=0;
  for(int i=0;i<count;i++){
    x[i]=0;
    if(taskSet[i].phase!=0){
      flag=1;
    }
    if(max<taskSet[i].p){
      max=taskSet[i].p;
      id=i;
    }
  }
  if(flag==0){
    return 0;
  }
  float inPhase=-1;
  float  ** array = calloc(sizeof(*array), count);
  for(int i=0;i<count;i++)
  {
  int n_jobs = (3*hp)/taskSet[i].p;
  array[i] = calloc(sizeof(**array), n_jobs+1 ); 
  array[i][0] = taskSet[i].phase;
  for(int j=1;j<=n_jobs;j++)
  {
  array[i][j] = array[i][j-1] + taskSet[i].p;
  }
  }
  for( ; x[id] <= (3*hp)/taskSet[id].p; x[id]++ ) {
        float val = array[id][x[id]];
        int print = 1;
        for( int i = 0; i < count; i++ ) {
          if(i==id){
            continue;
          }
            while (x[i] <= (3*hp)/taskSet[i].p && array[i][x[i]] < val ) {
              x[i]++;
            }
            if (array[i][x[i]] != val) print = 0;
        }
        if (print==1){
          inPhase=val;
          break;
        }
    }
    free(x);
    free(array);
  return inPhase;
}


float FindScheduleEnd(float inPhaseTime,float hyperperiod)
{
    float end;
    if(inPhaseTime==0)
    {
    end=3*hyperperiod;
    }
    else if(inPhaseTime==-1)
    {
      end=3*hyperperiod;
    }
    else
    {
      end=(inPhaseTime+hyperperiod)>(3*hyperperiod)?3*hyperperiod:inPhaseTime+hyperperiod;
    }
  return end;
}