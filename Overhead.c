#include"scheduler.h"

struct job* AddOverheadToSchedule(struct job* schedule,int *noOfJobsInSchedule,float *current,int *noOfOverheads,bool isDesionOverhead)
{
    //create a job with overhead
    schedule=AddOverheadJob(schedule,*noOfJobsInSchedule,*current,*noOfOverheads,isDesionOverhead);
    (*noOfJobsInSchedule)++;
    (*current)+=0.1;
    (*noOfOverheads)+=1;
    return schedule;
}



struct job* AddOverheadJob(struct job* schedule,int noOfJobsInSchedule,float current,int noOfOverheads,bool isDesionOverhead)
{
    schedule=(struct job*)realloc(schedule,(noOfJobsInSchedule*sizeof(struct job))+sizeof(struct job));
    //assign the job for decision overhead
    schedule[noOfJobsInSchedule].startTime=current;
    //add  0.1 and 0.2 for premption overhead
    schedule[noOfJobsInSchedule].endTime=current+=(isDesionOverhead?0.1:0.2);
    schedule[noOfJobsInSchedule].associatedTask=NULL;
    schedule[noOfJobsInSchedule].absoluteDeadline=0.0;
    schedule[noOfJobsInSchedule].id[0]=0;
    schedule[noOfJobsInSchedule].id[1]=0;
    schedule[noOfJobsInSchedule].id[2]=noOfOverheads;
    schedule[noOfJobsInSchedule].isOverhead=true;
    schedule[noOfJobsInSchedule].jobType=(isDesionOverhead?contextOverhead:preemptionOverhead);
    return schedule;
}