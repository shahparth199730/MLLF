/******************************************************************************************************************
WaitingTime will calculate the response time of all the jobs in the taskset. Will find absolute response jitter, relative response jitter,minimum, maximum and average response time for all the tasks.
******************************************************************************************************************/
void ResponseTime(struct jobs* job,struct task t,FILE *fptr,int count,float k){
  float *response;
  for(int j=0;j<count;j++){
    int n=(k-t.phase[j])/t.p[j];
    response=(float *)malloc(sizeof(float)*n);
    int id=0;
    float min=FLT_MAX,max=FLT_MIN;
    float rmax=FLT_MIN;
    float ravg=0;
    fprintf(fptr,"ResponseTime for Task T%d:\n",j+1);
    for(int i=0;id<n;i++){
      if(job[i].job_id==j+1){
      response[id]=job[i].finish-job[i].arrival;
      fprintf(fptr,"J%d,%d : %.2f ",job[i].job_id,job[i].instance_id,response[id]);
      if(min>response[id]){
        min=response[id];
      }
      if(max<response[id]){
        max=response[id];
      }
      if(id!=0){
        if(response[id]>response[id-1]){
          if(rmax<(response[id]-response[id-1])){
            rmax=response[id]-response[id-1];
          }
        }
        else{
          if(rmax<(response[id-1]-response[id])){
            rmax=response[id-1]-response[id];
          }
        }
      }
      ravg+=response[id];
      id++;
    }
  }
    if(response[0]>response[n-1]){
      if(rmax<response[0]-response[n-1]){
        rmax=response[0]-response[n-1];
      }
    }
    else{
      if(rmax<response[n-1]-response[0]){
        rmax=response[n-1]-response[0];
      }
    }
    fprintf(fptr,"\n");
    fprintf(fptr,"Max ResponseTime:%.2f and Min ResponseTime:%.2f\n",max,min);
    fprintf(fptr,"Absolute ResponseTime Jitter:%.2f\n",max-min);
    fprintf(fptr,"Relative ResponseTime Jitter:%.2f\n",rmax);
    fprintf(fptr,"Average ResponseTime:%.2f\n",ravg/n);
  }
  /*Freeing the dynamically allocated memory.*/
  free(response);
}
