void WaitingTime(struct jobs* job,struct task t,FILE *fptr,int count,float k){
  float *waiting;
  for(int j=0;j<count;j++){
    int n=(k-t.phase[j])/t.p[j];
    //printf("vaue of n is %d\n",n);
    waiting=(float *)malloc(sizeof(float)*n);
    int id=0;
    float min=FLT_MAX,max=FLT_MIN;
    float wavg=0;
    fprintf(fptr,"WaitingTime for Task T%d:\n",j+1);
    for(int i=0;id<n;i++){
      if(job[i].job_id==j+1){
        waiting[id]=job[i].finish-job[i].arrival-t.c[j];
        if(waiting[id]<0) waiting[id]=0;
        fprintf(fptr,"J%d,%d : %.2f ",job[i].job_id,job[i].instance_id,waiting[id]);
        if(min>waiting[id]){
          min=waiting[id];
        }
        if(max<waiting[id]){
          max=waiting[id];
        }
        wavg+=waiting[id];
        id++;
      }
    }
    fprintf(fptr,"\n");
    fprintf(fptr,"Max WaitingTime:%.2f and Min WaitingTime:%.2f\n",max,min);
    fprintf(fptr,"Average WaitingTime:%.2f\n",wavg/n);
  }
  free(waiting);
}
