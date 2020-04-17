#include"scheduler.h"

int FindTMIN(struct task *taskSet,int noOfTasks,int nextTaskID,float current,float curMinLatency,float *execArr)
{
    //TMin is the one which has earliest deadline among all the tasks and latency greater than the current task latency
    int i,tmin=0;
    float curTaskDeadline=*(execArr+(nextTaskID-1)*2)+taskSet[nextTaskID-1].p;
    for(i=0;i<noOfTasks;i++)
    {
        if(i!=nextTaskID)
        {
            //t min is such a task
            //1. not finished yet *********
            //2. has a deadline earlier than the current job scheduled 
            //3. ha laxity greater than the current scheduled one
            float laxity=FindLaxity(taskSet,i+1,execArr,current);
            if(i!=nextTaskID-1 && *(execArr+i*2+1)>0.1 && (*(execArr+i*2)+taskSet[i].p)< (*(execArr+(nextTaskID-1)*2)+taskSet[(nextTaskID-1)].p)
            &&laxity>curMinLatency)
                tmin=i+1;
            
            
            
            /*//deadline must be greater than current and nearest i.e.., nearer than current task's deadline
            if((*(execArr+i*2))+taskSet[i].p<curTaskDeadline && (j==0 || (*(execArr+2*i))+taskSet[i].p<(*(execArr+2*(tmin-1))+taskSet[tmin-1].p)))
            {
                tmin=i+1;
                j++;
            }*/

        }
    }
    return tmin;
}