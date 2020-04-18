/******************************************************************************************************************
Inphase module will check if there's no job having phase non-zero it will return 0. Else it will try to find the inphase point if any till 2*hp(because we will take minimum of 3*hp and first inPhase+hp).
******************************************************************************************************************/
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
  for(int i=0;i<count;i++){
    int n_jobs = (2*hp)/period[i];
    array[i] = calloc(sizeof(**array), n_jobs+1 );
    array[i][0] = phase[i];
    for(int j=1;j<=n_jobs;j++){
      array[i][j] = array[i][j-1] + period[i];
    }
  }
  for( ; x[id] <= (2*hp)/period[id]; x[id]++ ) {
    float val = array[id][x[id]];
    int print = 1;
    for( int i = 0; i < count; i++ ) {
      if(i==id){
        continue;
      }
      while (x[i] <= (2*hp)/period[i] && array[i][x[i]] < val ) {
        x[i]++;
      }
      if (array[i][x[i]] != val) print = 0;
    }
    if (print==1){
      inPhase=val;
      break;
    }
  }
    /*Freeing the dynamically allocated memory.*/
    free(x);
    free(array);
  return inPhase;
}
