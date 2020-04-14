#include"scheduler.h"

int main(){
   FILE *fp;
   struct periodicTask *t;
   struct sporadicJob *s,*rq,*sort_rq;
   struct aperiodicJob *aper;
   int no_PeriodicTasks,hyperPeriod,len_rq,heap_Size,i; 
   bool isSchedulable;
   //read the no of periodic jobs
   no_PeriodicTasks=readFile(&fp);
   t=readPeriodicTaskSet(fp,no_PeriodicTasks);
   isSchedulable=checkFeas(t,no_PeriodicTasks);
   if(isSchedulable)
   {
      hyperPeriod=calcHyperPeriod(t,no_PeriodicTasks);
      // calculateSlack(t,no_PeriodicJobs,0);
   }
   else
      printf("Given taskset is not schedulable, please try with another taskset");
   
   return 0;
}
