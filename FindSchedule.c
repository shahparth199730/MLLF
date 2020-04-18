/******************************************************************************************************************
In this module ,will create the jobs dynamically. Will start the counter from 0 and will take the jobs whose arrival is less than or equal to counter value. For every point Scheduler function will call which will select which job to be executed. At the end of the schedule will call ResponseTime and WaitingTime module to calculate response time and waiting time of different jobs in the schedule.
******************************************************************************************************************/
#include"Scheduler.c"
#include"CreateNewJob.c"
#include"Comparator.c"
#include"ResponseTime.c"
#include"WaitingTime.c"
int FindSchedule(struct task t,float end,int count){
  struct jobs *job;
  int total=0,k=0;
  /*calculating the total jobs in the taskset from 0 to end o schedule.*/
  for(int i=0;i<count;i++){
    total+=((end-t.phase[i])/t.p[i]);
  }
  //printf("TOTAL JOBS ARE:%d\n\n",total);
  /*Initially allocating only memory for job of each task. And will increase using realloc as and when required.*/
  job=(struct jobs*)malloc(count*sizeof(struct jobs));
  for(int i=0;i<count;i++){
      job[k].job_id=i+1;
      job[k].instance_id=1;
      srand(time(0));
      float random=rand()%5;
      float value=((5+random)/10);
      float normalize=(float)((int)((t.c[i]*value) * 100 + .5))/100;
      job[k].execution=normalize;
      job[k].curr_execution=job[k].execution;
      job[k].visit=0;
      job[k].arrival=t.phase[i];
      job[k].deadline=job[k].arrival+t.d[i];
      job[k].finish=0;
      //printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[k].job_id,job[k].instance_id,job[k].execution,job[k].arrival,job[k].deadline);
      k++;
  }
  /*Sorting based on arrival.*/
  qsort(job, k, sizeof(struct jobs), comparator);
  struct laxity *l;
  int *ready_queue;
  FILE *fptr;
  int preemption=0,curr_job=-1,prev_job=-1,id_tracker=0,qend=0;
  float timer=0,counter=0;
  ready_queue=(int *)malloc(count*sizeof(int));
  fptr = fopen("periodicSchedule.txt", "w");
  if (fptr == NULL)
  {
      printf("Could not open file");
      return 0;
  }
  /*loop that will iterate till the counter variable reach to end of schedule.*/
  while(counter<end&&id_tracker<total||qend!=0){
    /*Checking for the jobs which have been arrived.*/
    for(int i=id_tracker;job[i].arrival<=counter;i++){
      if(id_tracker>=k) break;
      ready_queue[qend++]=i;
      id_tracker++;
      printf("READY QUEUE:%d\n",ready_queue[qend-1]);
    }
    /*If ready_queue is empty keep the cpu IDLE.*/
    if(0==qend){
      float tc=counter;
      counter=job[id_tracker].arrival;
      fprintf(fptr,"%.2f-%.2f : IDLE\n",tc,counter);
      continue;
    }
    counter+=0.1;
    l=(struct laxity *)malloc(qend*sizeof(struct laxity));
    int ik=0;
    /*Will caculate the laxity of the jobs in the ready_queue.*/
    for(int i=0;i<qend;i++){
      if(job[ready_queue[i]].visit!=1){
        l[ik].slack=job[ready_queue[i]].deadline-counter-job[ready_queue[i]].curr_execution;
        l[ik].id=ready_queue[i];
        l[ik].execution=job[ready_queue[i]].curr_execution;
        ik++;
      }
    }
    if(qend>1)
    qsort(l, qend, sizeof(struct laxity), Comparator);
    /*As the ready_queue are sorted based on laxity, will check if the first job in ready_queue is having negative slack, if so we will return that.*/
    if(l[0].slack<0){
      printf("J%d,%d misses the deadline.\n",job[l[0].id].job_id,job[l[0].id].instance_id);
      return 0;
    }
    float arr[2];
    arr[0]=curr_job;
    arr[1]=0;
    prev_job=curr_job;
    /*As decision point will be there will add 0.1 overhead.*/
    fprintf(fptr,"%.2f-%.2f : Decision Overhead\n",counter-0.1,counter);
    Scheduler(counter,job,qend,arr,l);
    /*arr[0] will contain the id of job seleccted for execution. arr[1] will contain condition c3: Dmin-slack of curr_job*/
    curr_job=arr[0];
    timer=arr[1];
    /*Will check if currently selected job is not same as previously executing job(seeing if its completed will ignore in that case.) then will add 0.2 overhead.*/
    if(prev_job!=-1&&curr_job!=prev_job&&job[prev_job].visit!=1){
      preemption++;
      counter+=0.2;
      fprintf(fptr,"%.2f-%.2f : Preemption Overhead\n",counter-0.2,counter);
    }
    /*Conditon c1: current job completing the execution.*/
    float c1=counter+job[curr_job].curr_execution;
    /*Next Job arrival*/
    float c2=job[id_tracker].arrival;
    float c;
    if(id_tracker<k){
      c=c1>c2?c2:c1;
    }
    else{
      c=c1;
    }
    if(timer>c||timer==-1){
      timer=c;
    }
    timer=(float)((int)(timer * 100 + .5))/100;
    counter=(float)((int)(counter * 100 + .5))/100;
    fprintf(fptr,"%.2f-%.2f : J%d,%d\n",counter,timer,job[curr_job].job_id,job[curr_job].instance_id);
    printf("Counter+JobExe=%f and timer:%f and %d\n",counter+job[curr_job].curr_execution,timer,counter+job[curr_job].curr_execution>=timer);
    if(counter+job[curr_job].curr_execution==timer){
      printf("MARKING J%d,%d as visited for %d\n",job[curr_job].job_id,job[curr_job].instance_id,curr_job);
      job[curr_job].visit=1;
      job[curr_job].curr_execution=0;
      job[curr_job].finish=timer;
      for(int i=0;i<qend;i++){
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
        qsort(job, k, sizeof(struct jobs), comparator);
      }
    }
    else{
      job[curr_job].curr_execution-=(timer-counter);
      job[curr_job].curr_execution=(float)((int)(job[curr_job].curr_execution * 100 + .5))/100;
    }
    counter+=(timer-counter);
    counter=(float)((int)(counter * 100 + .5))/100;
    timer=0;
    for(int i=0;i<qend;i++){
      printf("ReadQueue:%d\n",ready_queue[i]);
    }
  }
  /*After completing the schedule will check if there's any remaining time. If so we will display that as idle time.*/
  if(counter!=end){
    fprintf(fptr,"%.2f-%.2f : IDLE\n",counter,end);
  }
  fprintf(fptr,"\n");
  /*Printing the the total preemption.*/
  fprintf(fptr,"Total preemptions are:%d\n",preemption);
  fprintf(fptr,"\n");
  /*Calling the ResponseTime function which will calculate and print the response time and related parameters.*/
  ResponseTime(job,t,fptr,count,end);
  /*Calling the ResponseTime function which will calculate and print the waiting time and related parameters.*/
  WaitingTime(job,t,fptr,count,end);
  fclose(fptr);
  /*Freeing the dynamically allocated memory.*/
  free(job);
  free(ready_queue);
  free(l);
  return 1;
}
