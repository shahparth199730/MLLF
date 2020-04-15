#include"Scheduler.c"
#include"CreateNewJob.c"
#include"Comparator.c"
#include"ResponseTime.c"
#include"WaitingTime.c"
int FindSchedule(struct task t,float end,int count){
  struct jobs *job;
  int total=0;
  for(int i=0;i<count;i++){
    total+=((end-t.phase[i])/t.p[i]);
  }
  int k=0;
  printf("TOTAL JOBS ARE:%d\n\n",total);
  job=(struct jobs*)malloc(total*sizeof(struct jobs));
  for(int i=0;i<count;i++){
    if(t.phase[i]==0){
      job[k].job_id=i+1;
      job[k].instance_id=1;
      job[k].execution=t.c[i];
      job[k].visit=0;
      job[k].arrival=t.phase[i];
      job[k].deadline=job[k].arrival+t.d[i];
      job[k].finish=0;
      printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[k].job_id,job[k].instance_id,job[k].execution,job[k].arrival,job[k].deadline);
      k++;
    }
  }
  for(int i=0;i<count;i++){
    if(t.phase[i]!=0){
      job[k].job_id=i+1;
      job[k].instance_id=1;
      job[k].execution=t.c[i];
      job[k].visit=0;
      job[k].arrival=t.phase[i];
      job[k].deadline=job[k].arrival+t.d[i];
      job[k].finish=0;
      printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[k].job_id,job[k].instance_id,job[k].execution,job[k].arrival,job[k].deadline);
      k++;
    }
  }
  struct laxity *l;
  int *ready_queue;
  FILE *fptr;
  int preemption=0;
  float timer=0;
  float counter=0;
  int curr_job=-1;
  int prev_job=-1;
  int id_tracker=0;
  ready_queue=(int *)malloc(count*sizeof(int));
  int qend=0;
  fptr = fopen("periodicSchedule.txt", "w");
  if (fptr == NULL)
  {
      printf("Could not open file");
      return 0;
  }
  while(counter<end&&id_tracker<total||qend!=0){
    for(int i=id_tracker;job[i].arrival<=counter;i++){
      if(id_tracker>=k) break;
      ready_queue[qend++]=i;
      id_tracker++;
      printf("READY QUEUE:%d\n",ready_queue[qend-1]);
    }
    if(0==qend){
      float tc=counter;
      counter=job[id_tracker].arrival;
      fprintf(fptr,"%.2f-%.2f : IDLE\n",tc,counter);
      continue;
    }
    l=(struct laxity *)malloc(qend*sizeof(struct laxity));
    int ik=0;
    for(int i=0;i<qend;i++){
      if(job[ready_queue[i]].visit!=1){
        l[ik].slack=job[ready_queue[i]].deadline-counter-job[ready_queue[i]].execution;
        l[ik].id=ready_queue[i];
        l[ik].execution=job[ready_queue[i]].execution;
        ik++;
      }
    }
    if(qend>1)
    qsort(l, qend, sizeof(struct laxity), Comparator);
    if(l[0].slack<0){
      printf("J%d,%d misses the deadline.\n",job[l[0].id].job_id,job[l[0].id].instance_id);
      return 0;
    }
    float arr[2];
    arr[0]=curr_job;
    arr[1]=0;
    prev_job=curr_job;
    counter+=0.1;
    Scheduler(counter,job,qend,arr,l);
    curr_job=arr[0];
    timer=arr[1];
    if(prev_job!=-1&&curr_job!=prev_job&&job[prev_job].visit!=1){
      preemption++;
      counter+=0.2;
    }
    float temp_timer1=counter+job[curr_job].execution;
    float temp_timer2=job[id_tracker].arrival;
    float temp_timer;
    if(id_tracker<k){
      temp_timer=temp_timer1>temp_timer2?temp_timer2:temp_timer1;
    }
    else{
      temp_timer=temp_timer1;
    }
    if(timer>temp_timer||timer==-1){
      timer=temp_timer;
    }
    fprintf(fptr,"%.2f-%.2f : J%d,%d\n",counter,timer,job[curr_job].job_id,job[curr_job].instance_id);
    if(counter+job[curr_job].execution==timer){
      printf("MARKING J%d,%d as visited for %d\n",job[curr_job].job_id,job[curr_job].instance_id,curr_job);
      job[curr_job].visit=1;
      job[curr_job].execution=0;
      job[curr_job].finish=timer;
      for(int i=0;i<qend-1;i++){
        if(ready_queue[i]==curr_job){
          ready_queue[i]=ready_queue[i+1];
          ready_queue[i+1]=curr_job;
        }
      }
      qend--;
        if(id_tracker<total){
        struct jobs *newjob = (struct jobs *)realloc(job, sizeof(struct jobs)*(k+1));
        if(newjob==NULL){
          printf("Memory error");
          return 0;
        }
        job=newjob;
      CreateNewJob(job,t,&k,curr_job);
    }
    }
    else{
      job[curr_job].execution-=(timer-counter);
    }
    counter+=(timer-counter);
    counter=(float)((int)(counter * 1000 + .5))/1000;
    timer=0;
  }
  if(counter!=end){
    fprintf(fptr,"%.2f-%.2f : IDLE\n",counter,end);
  }
  fprintf(fptr,"\n");
  fprintf(fptr,"Total preemptions are:%d\n",preemption);
  fprintf(fptr,"\n");
  ResponseTime(job,t,fptr,count,end);
  WaitingTime(job,t,fptr,count,end);
  fclose(fptr);
  free(job);
  free(ready_queue);
  free(l);
  return 1;
}
