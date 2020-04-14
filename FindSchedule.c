#include"Scheduler.c"
int comparator(const void *p, const void *q)
{
    struct jobs* l1 = (struct jobs *)p;
    struct jobs* r1 = (struct jobs *)q;
    float l=l1->arrival;
    float r=r1->arrival;
    if(l-r>0){
      return 1;
    }
    else if(l-r==0){
      float temp1=((struct jobs *)p)->deadline;
      float temp2=((struct jobs *)q)->deadline;
      if(temp1<temp2){
        return -1;
      }
      else{
        return 1;
      }
    }
    else{
      return -1;
    }
    return -1;
}
int compare(const void *p, const void *q)
{
    struct laxity* l1 = (struct laxity *)p;
    struct laxity* r1 = (struct laxity *)q;
    float l=l1->slack;
    float r=r1->slack;
    if(l-r>0){
      return 1;
    }
    else if(l-r==0){
      float temp1=((struct laxity *)p)->execution;
      float temp2=((struct laxity *)q)->execution;
      if(temp1<temp2){
        return -1;
      }
      else{
        return 1;
      }
    }
    else{
      return -1;
    }
    return -1;
}
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
    int n=(end-t.phase[i])/t.p[i];
    for(int j=0;j<n;j++){
      job[k].job_id=i+1;
      job[k].instance_id=j+1;
      job[k].execution=t.c[i];
      job[k].phase=t.phase[i];
      job[k].visit=0;
      if(j==0){
        job[k].arrival=t.phase[i];
      }
      else{
        job[k].arrival=job[k-1].arrival+t.p[i];
      }
      job[k].deadline=job[k].arrival+t.d[i];
      job[k].finish=0;
      printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[k].job_id,job[k].instance_id,job[k].execution,job[k].arrival,job[k].deadline);
      k++;
    }
  }
  printf("After Sorting:\n");
  qsort(job, k, sizeof(struct jobs), comparator);
  for(int i=0;i<k;i++){
    printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[i].job_id,job[i].instance_id,job[i].execution,job[i].arrival,job[i].deadline);
  }
  int preemption=0;
  float timer=0;
  float counter=0;
  int curr_job=-1;
  int prev_job=-1;
  int id_tracker=0;
  int *ready_queue=(int *)malloc(3*sizeof(int));
  int qend=0;
  FILE *fptr;
    fptr = fopen("periodicSchedule.txt", "w");
  if (fptr == NULL)
  {
      printf("Could not open file");
      return 0;
  }
  while(counter<end/3&&id_tracker<k){
    //int count=0;
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

    struct laxity *l;
    l=(struct laxity *)malloc(qend*sizeof(struct laxity));
    int ik=0;
    for(int i=0;i<qend;i++){
      //printf("l[ik]:%d",ready_queue[i]);
      if(job[ready_queue[i]].visit!=1){
        l[ik].slack=job[ready_queue[i]].deadline-counter-job[ready_queue[i]].execution;
        l[ik].id=ready_queue[i];
        l[ik].execution=job[ready_queue[i]].execution;
        ik++;
      }
    }
    if(qend>1)
    qsort(l, qend, sizeof(struct laxity), compare);


    float arr[3];
    arr[0]=curr_job;
    arr[1]=0;
    arr[3]=total;
    prev_job=curr_job;
    Scheduler(counter,job,qend,arr,l);
    curr_job=arr[0];
    timer=arr[1];
    if(prev_job!=-1&&curr_job!=prev_job&&job[prev_job].visit!=1){
      preemption++;
      //counter+=0.2;
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
      // for(int i=qstart;i<qend;i++){
      //   printf("BEFORE JOB id's are:%d\n",ready_queue[i]);
      // }
      //int  move_id=-1;
      for(int i=0;i<qend-1;i++){
        if(ready_queue[i]==curr_job){
          ready_queue[i]=ready_queue[i+1];
          ready_queue[i+1]=curr_job;
          //printf("ON JOB id's are:%d\n",ready_queue[i]);
          //break;
        }
      }
      // for(int i=qend-1;i>=moveid;i--){
      //   reeady
      // }
      qend--;
      // for(int i=qstart;i<qend;i++){
      //   printf("JOB id's are:%d\n",ready_queue[i]);
      // }
    }
    else{
      job[curr_job].execution-=(timer-counter);
    }
    counter+=(timer-counter);
    counter=(float)((int)(counter * 1000 + .5))/1000;
    timer=0;
    //counter+=0.1;
    //if(curr_job==43) break;
    // printf("Hello\n");
  //}
  }
  if(counter!=end){
    fprintf(fptr,"%.2f-%.2f : IDLE\n",counter,end);
  }
  fprintf(fptr,"Total preemptions are:%d\n",preemption);
  for(int i=0;i<k;i++){
    float resposne=job[i].finish-job[i].arrival;
    printf("Respone time for job J%d,%d having arrival:%f and finishing:%f :: %f\n",job[i].job_id,job[i].instance_id,job[i].arrival,job[i].finish,resposne);
  }
  fclose(fptr);
  return 1;
}
