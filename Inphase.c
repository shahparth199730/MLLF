float Inphase(float* phase,float* period, int count,float hp){
  int *x=(int *)malloc(count*sizeof(int));
  float max=0.0;
  int id=-1;
  int flag=0;
  for(int i=0;i<count;i++){
    x[i]=0;
    if(phase[i]!=0){
      flag=1;
    }
    if(max<period[i]){
      max=period[i];
      id=i;
    }
  }
  if(flag==0){
    return 0;
  }
  float inPhase=-1;
  float  ** array = calloc(sizeof(*array), count);
  for(int i=0;i<count;i++)
  {
  int n_jobs = (3*hp)/period[i];
  array[i] = calloc(sizeof(**array), n_jobs+1 ); // No. of Jobs in each tasks
  printf("No of Jobs in Task %dth Task = %d \n",(i+1),n_jobs);
  array[i][0] = phase[i];
  for(int j=1;j<=n_jobs;j++)
  {
  array[i][j] = array[i][j-1] + period[i];
  printf("%f\t",array[i][j-1]);
  }
  printf("\n");
  }
  for( ; x[id] <= (3*hp)/period[id]; x[id]++ ) {
        float val = array[id][x[id]];
        printf("1val is :%f\n",val);
        int print = 1;
        for( int i = 0; i < count; i++ ) {
          if(i==id){
            continue;
          }
          printf("For task %d\n",i);
            while (x[i] <= (3*hp)/period[i] && array[i][x[i]] < val ) {
              x[i]++;
              printf("%f ",array[i][x[i]]);
            }
            if (array[i][x[i]] != val) print = 0;
            printf("\n");
        }
        if (print==1){
          printf("VALUE is:%f\n",val);
          inPhase=val;
          break;
        }
    }
    free(x);
    free(array);
  return inPhase;
}
