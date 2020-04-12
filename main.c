#include"myheader.h"

int main(){
   FILE *fp;
   struct periodicTask *t;
   struct sporadicJob *s,*rq,*sort_rq;
   struct aperiodicJob *aper;
   int no_PeriodicJobs,no_SporadicJobs,no_AperiodicJobs,hyperPeriod,f,tot_frames,len_rq,heap_Size; ;
   no_PeriodicJobs=readFile(&fp);
   t=readPeriodicJob(fp,no_PeriodicJobs);
   checkFeas(t,no_PeriodicJobs);
   hyperPeriod=calcHyperPeriod(t,no_PeriodicJobs);
   calculateSlack(t,no_PeriodicJobs,0);
   return 0;
}
