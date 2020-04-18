#include"scheduler.h"
#include"scheduler.h"

void WriteJobToFile(float startTime,float endTime,int jobID1,int jobID2,bool isIdle)
{
    FILE *fp;
    fp=fopen("FinalSchedule.txt","a");
    if(fp!=NULL)
    {
        if(!isIdle)
            fprintf(fp,"Job ID: %d %d (%.2f-%.2f)\n",jobID1,jobID2,startTime,endTime);
        else
            fprintf(fp,"Idle Time (%.2f-%.2f)\n",startTime,endTime);
    }
    else
    printf("Error in writing the schedule to the file");
    fclose(fp);
}

void WriteOverHeadToFile(float startTime,bool isDecisionOverhead)
{
    FILE *fp;
    fp=fopen("FinalSchedule.txt", "a");
    if(fp!=NULL)
    {
        if(isDecisionOverhead)
            fprintf(fp,"Decision Overhead: (%.2f-%.2f)\n",startTime,startTime+0.1);
        else
            fprintf(fp,"Preemption Overhead: (%.2f-%.2f)\n",startTime,startTime+0.2);

    }
    fclose(fp);
}