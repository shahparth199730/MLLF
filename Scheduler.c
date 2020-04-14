#include"TieBreaker.c"
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

void Scheduler(float counter,struct jobs *job,int qstart,int qend,float *arr,int *ready_queue){
  int n=qend-qstart;
  struct laxity *l;
  l=(struct laxity *)malloc(n*sizeof(struct laxity));
  int ik=0;
  float min_deadline=0;
  int min_id=-1;
  for(int i=qstart;i<qend;i++){
    //printf("l[ik]:%d",ready_queue[i]);
    if(job[ready_queue[i]].visit!=1){
      l[ik].slack=job[ready_queue[i]].deadline-counter-job[ready_queue[i]].execution;
      l[ik].id=ready_queue[i];
      l[ik].execution=job[ready_queue[i]].execution;
      ik++;
    }
  }
  if(n>1)
  qsort(l, n, sizeof(struct laxity), compare);
  min_deadline=job[l[0].id].deadline;
  for(int i=1;i<n;i++){
      if(min_deadline>job[l[i].id].deadline){
        min_deadline=job[l[0].id].deadline;
        min_id=l[i].id;
      }
      if(l[0].slack==l[i].slack){
        TieBreaker(job,l,i,arr[0],&min_deadline,&min_id);
      }
    printf("Job:%d,%d, with slack %f and execution:%f and deadline:%f\n",job[l[i].id].job_id,job[l[i].id].instance_id,l[i].slack,l[i].execution,job[l[i].id].deadline);
  }
  // float c=INT_MAX;
  // if(qend<arr[3]){
  //   c=job[qend].arrival;
  // }
  // printf("C1:%f\n",c1);
  // printf("l[0].id:%d\n",l[0].id);
  // //float c2=counter+l[0].execution;
  // printf("C2:%f\n",c2);
  // float c;
  // if(qend<arr[3]){
  //   c=c1>c2?c2:c1;
  // }
  // else{
  //   c=c2;
  // }
  float c3=-1;
  if(min_id!=-1){
    c3=job[min_id].deadline-l[0].slack;
    // if(c>c3){
    //   c=c3;
    //   printf("*********C3 is selected value is:%f.\n\n",c3);
    // }
  }
  arr[0]=l[0].id;
  arr[1]=c3;
  return;
}
