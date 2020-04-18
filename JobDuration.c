#include"scheduler.h"

float FindJobDuration(int nextTaskID,struct task *taskSet,float *execArr,float current,int noOfTasks,float end,float curMinLaxity)
{
    float duration,nextTaskArrival,currentTaskOver,nearestEvent,tq,tqOverEvent;
    int tmin;
    /*3 events until next job
        1. new job comes
        2. current task over
        3. TQ expires
    */
    //1.new job comes
    nextTaskArrival=FindNextTaskArrival(taskSet,execArr,current,noOfTasks,end);
    currentTaskOver= current+*(execArr+(nextTaskID-1)*2+1);
    nearestEvent=(nextTaskArrival!=0&&nextTaskArrival<currentTaskOver?nextTaskArrival:currentTaskOver);
    //Time Quantum
    tmin=FindTMIN(taskSet,noOfTasks,nextTaskID,current,curMinLaxity,execArr);
    if(tmin!=0)
    {
        //time quantum=deadline of the min-current laxity
        tq=*(execArr+2*(tmin-1))-curMinLaxity;
        tqOverEvent=current+tq;
        nearestEvent=(tqOverEvent<nearestEvent?tqOverEvent:nearestEvent);
    }
  
    //TODO: verify if next task arrival is not 0
    //Duration=nextEventTime-current;
    duration=nearestEvent-current;
    return duration;
}