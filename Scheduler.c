/******************************************************************************************************************
This will select which job to execute and return the job id back to the FindSchedule function. If there is tie int the laxity it will call the TieBreaker which will break the tie by selecting the curre job which was executing.
******************************************************************************************************************/
#include"TieBreaker.c"
void Scheduler(float counter,struct jobs *job,int qend,float *arr,struct laxity *l){
  float min_deadline=0;
  int min_id=-1;
  min_deadline=job[l[0].id].deadline;
  printf("Job:%d,%d, with slack %f and execution:%f and deadline:%f\n",job[l[0].id].job_id,job[l[0].id].instance_id,l[0].slack,l[0].execution,job[l[0].id].deadline);
  for(int i=1;i<qend;i++){
      if(min_deadline>job[l[i].id].deadline){
        min_deadline=job[l[0].id].deadline;
        min_id=l[i].id;
      }
      if(l[0].slack==l[i].slack){
        TieBreaker(job,l,i,arr[0],&min_deadline,&min_id);
      }
    printf("Job:%d,%d, with slack %f and execution:%f and deadline:%f\n",job[l[i].id].job_id,job[l[i].id].instance_id,l[i].slack,l[i].execution,job[l[i].id].deadline);
  }
  printf("\n");
  /*Finding the condition c3: If any deadline is found which is less than the currently selected job's deadline will make the decision point such as difference of minimum deadline and laxity of current job.*/
  float c3=-1;
  if(min_id!=-1){
    c3=job[min_id].deadline-l[0].slack;
  }
  arr[0]=l[0].id;
  arr[1]=c3;
  return;
}
