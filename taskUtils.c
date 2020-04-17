
#include"scheduler.h"

bool CreateSchedule(char* fileName)
{
  //read the taskset from the file
    bool res=false;
    int noOfTasks=0,*count,noOfJobs,*jobCount;
    count=&noOfTasks;
    struct task *taskSet=InitializeTaskSet(fileName,count);
    if(taskSet!=NULL)
    {
        float hyperperiod,inPhaseTime,start=0.0,end;
        struct job *schedule;
        jobCount=&noOfJobs;
        PrintTaskSet(taskSet,*count);
        if(CheckTaskSetFeasibility(taskSet,noOfTasks))
        {
          hyperperiod=CalculateHyperPeriod(taskSet,*count);
          PrintHyperPeriod(hyperperiod);
          inPhaseTime=Inphase(taskSet, *count,hyperperiod);
          end=FindScheduleEnd(inPhaseTime,hyperperiod);
          schedule=FindFeasibleSchedule(taskSet,end,noOfTasks,jobCount);
          res=true;
        }
    }
    return res; 
}








