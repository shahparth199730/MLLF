#include"scheduler.h"


void FindFeasibleSchedule(struct task* taskSet,float end,int noOfTasks,int *jobCount)
{
    //TODO; free such arrays not needed in the end
    //Arrays that might be freed 
    float *execArr=NULL,cur,duration,*minLax,minLaxityVal;
    minLax=&minLaxityVal;
    bool isPrevJobFinished;
    int *latestSubJobIdArr=(int *)malloc(noOfTasks*sizeof(int));
    int *activeTaskCount,AtCount=0,i,*activeTasks,prevTaskID=0,nextTaskID;
    activeTaskCount=&AtCount;
    //initialize the task id array
    execArr=CreateExecutionTimeArr(noOfTasks);
    InitializeExecutionTimeArr(execArr,taskSet,noOfTasks);
    //just open file in writing mode to ensure it is clean
    FILE *fp;
    fp=fopen("FinalSchedule.txt","w");
    fclose(fp);
    //initially find currently active tasks at 
    while(cur<end)
    {
        //elapse 0.1 sec for decision making
        WriteOverHeadToFile(cur,true);
        cur+=0.1;        
        //among the available tasks, look for the tasks available
        //TODO: how do we ensure the granularity of 0.1
        *activeTaskCount=0;
        printf("\n\n\n");
        activeTasks=FindCurrentlyActiveTasks(execArr,noOfTasks,cur,activeTaskCount);
        printf("Cur is %.2f\n",cur);
        printf("General info for current tasks\n");
        for(i=0;i<noOfTasks;i++)
        {
            printf("Task ID: %d Arrival Time: %.2f Rem Exec Time:%.2f\n",i+1
            ,*(execArr+i*2),*(execArr+i*2+1));
        }
        printf("Below is the list of active tasks with count %d\n",*activeTaskCount);
        for(int i=0;i<*activeTaskCount;i++)
        {
            printf("Task ID: %d Arrival Time: %.2f Rem Exec Time:%.2f\n",activeTasks[i]
            ,*(execArr+(activeTasks[i]-1)*2),*(execArr+(activeTasks[i]-1)*2+1));
        }
        //TODO: if active tasks is null, wait till the next job arrives
        //active count 0 means that 
        //1.either time is up
        //2. cpu remains idle for sometime.
        if((*activeTaskCount)==0)
        {
            float nextJobArrival= getNextJobArrivalTime(execArr,cur,noOfTasks);
            WriteJobToFile(cur,(cur+(nextJobArrival-cur)),0,0,true);
            cur+=(nextJobArrival-cur);
            continue;
        }
        nextTaskID=FindNextTaskToBeScheduled(activeTasks,*activeTaskCount,cur,taskSet,execArr,prevTaskID,minLax);
        //means no next task present, so simply exit
        
        //check if job prempted i.e.., job was asked to leave but not complete yet
        //elapse the time in case of job preemption
        if(prevTaskID!=0 && nextTaskID!=prevTaskID && !isPrevJobFinished)
        {
            WriteOverHeadToFile(cur,false);
            cur+=0.2;
        }
    
        //for duration, look when the next event occurs 1. new job come 2. TQ expires 3. job finishes(find the min among these)
        duration=FindJobDuration(nextTaskID,taskSet,execArr,cur,noOfTasks,end,*minLax);
        printf("Next Task ID %d and Duration %f aur cur hae %.2f and pehle remaining %f\n",nextTaskID,duration,cur
        ,(*(execArr+(nextTaskID-1)*2+1)));
        //printf("five exe %f\n",5.0-5.0);
         //printf("Remaining is %.2f and reset hua %d\n",(*(execArr+(nextTaskID-1)*2+1))-duration,duration>=*(execArr+(nextTaskID-1)*2+1));
        WriteJobToFile(cur,cur+duration,nextTaskID,floor((*(execArr+(nextTaskID-1)*2))/taskSet[nextTaskID-1].p)+1,false);
        cur+=duration; 
        //TODO: increase cur
        //TODO : write to the file 
        //duration==remaining execution time for that task,job is done
        if(duration>=*(execArr+(nextTaskID-1)*2+1))
        {
            //if job finished,reinitialize the jobid for that task,else update the latestJobID for the task executed
            isPrevJobFinished=true;
            //reset next job, and set the sub job array count to 1
            ResetNextJob(taskSet,execArr,nextTaskID);
            latestSubJobIdArr[nextTaskID-1]=1;
        }
        else
        {
            //reduce the duration from remaining exec time
            (*(execArr+(nextTaskID-1)*2+1))-=duration;
            isPrevJobFinished=false;
            latestSubJobIdArr[nextTaskID-1]++;
        }
       
        //TODO: also set isPrevJobFinished
        //TODO: change the random
        prevTaskID=nextTaskID;
        //if(j>=30)
        //break;
    }
    free(execArr);
    free(latestSubJobIdArr);
    free(activeTasks);
}












