#include"scheduler.h"

struct job *AddJobToSchedule(struct job* schedule,struct task *taskSet,int nextTaskID,float duration,float *execArr,float *cur,int* noOfJobsInSchedule,int latestSubJobId)
{
    //TODO: increment number of jobs
    
    //create a job
    schedule=(struct job*) realloc(schedule,*noOfJobsInSchedule*sizeof(struct job)+sizeof(struct job));
    //execArr has job's arrival time only
    schedule[*noOfJobsInSchedule].id[0]=nextTaskID;
    schedule[*noOfJobsInSchedule].id[1]=floor((*(execArr+(nextTaskID-1)*2))/taskSet[nextTaskID-1].p)+1;
    schedule[*noOfJobsInSchedule].id[2]=latestSubJobId;
    schedule[*noOfJobsInSchedule].startTime=*cur;
    schedule[*noOfJobsInSchedule].endTime=*cur+duration;
    schedule[*noOfJobsInSchedule].associatedTask=taskSet+nextTaskID-1;
    schedule[*noOfJobsInSchedule].absoluteDeadline=*(execArr+(nextTaskID-1)*2)+taskSet[nextTaskID-1].p;
    //incrememt current by the duration
    printf("cur pehle was %.2f\n",*cur);
    *cur+=duration;
    (*noOfJobsInSchedule)++;
    return schedule;
}