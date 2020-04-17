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
    printf("\n\n\nNext task arrival at %.2f\n",nextTaskArrival);
    currentTaskOver= current+*(execArr+(nextTaskID-1)*2+1);
    printf("Current task over at %.2f\n",currentTaskOver);
    nearestEvent=(nextTaskArrival!=0&&nextTaskArrival<currentTaskOver?nextTaskArrival:currentTaskOver);
    //Time Quantum
    tmin=FindTMIN(taskSet,noOfTasks,nextTaskID,current,curMinLaxity,execArr);
    printf("Tmin exists %d\n",tmin!=0);
    if(tmin!=0)
    {
        //time quantum=deadline of the min-current laxity
        tq=*(execArr+2*(tmin-1))-curMinLaxity;
        printf("tmin is %d and tq for t min is %.2f\n",tmin,tq);
        tqOverEvent=current+tq;
        nearestEvent=(tqOverEvent<nearestEvent?tqOverEvent:nearestEvent);
    }
  
    //TODO: verify if next task arrival is not 0
    //Duration=nextEventTime-current;
    printf("current si apna%.2f\n",current);
    duration=nearestEvent-current;
    return duration;
}