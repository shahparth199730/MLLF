/********************************************************************************************************************
In this module, will read the taskset from the given file. Check for the utilization. If it's more than 1 we will display the not schedulable message and return. If it's not more than 1, we will find the HyperPeriod followed by inphase point if any and based on that we will decide the schedule. The schedule will begin from 0 and end with minimum of 3*HyperPeriod or first inphase point+HyperPeriod.
********************************************************************************************************************/
#include"HyperPeriod.c"
#include"Inphase.c"
#include"FindSchedule.c"
void Handler(char *filename){
  /* filename parameter contains name of file taken from commandline */
  FILE *fp1 = fopen( filename, "r" );
  FILE *fp2 = fopen( filename, "r" );
  int count=0;
  char ch;
  int i=0;
  float utilization=0;
  float hp;
  struct task t;
  if ( fp1 == NULL )
  {
      printf( "Could not open file\n" );
      return;
  }
  for (ch = getc(fp1); ch != EOF; ch = getc(fp1)) {
    if (ch == '\n'){
      count = count + 1;
    }
  }
  fclose( fp1 );
  /*Dynamic memory allocation for the tasks inf the taskset.*/
  t.phase=(float *)malloc(count*sizeof(float));
  t.p=(float *)malloc(count*sizeof(float));
  t.d=(float *)malloc(count*sizeof(float));
  t.c=(float *)malloc(count*sizeof(float));
  /* Reading the taskset from the given file.*/
  while (fscanf(fp2, "%f,%f,%f,%f\n",&t.phase[i],&t.p[i], &t.c[i], &t.d[i])==4) {
    //printf("%f,%f,%.1f,%f\n", t.phase[i],t.p[i], t.c[i], t.d[i]);
    i++;
  }
  fclose( fp2 );
  /*Finding the utilization */
  for(int i=0;i<count;i++){
      utilization+=(t.c[i]/t.p[i]);
  }
  /*IF utilization>1 we will return with the display message.*/
  if(utilization>1.0){
    printf("utilization:%f so not scheduleable.\n",utilization);
    return;
  }
  /*Finding the hyperperiod.*/
  hp=HyperPeriod(t.p,count);
  //printf("hp is: %f\n",hp);
  /*finding the inphase point for the taskset.*/
  float fip=Inphase(t.phase,t.p,count,hp);
  float end=0;
  /*If return value is 0 it means all jobs are inphase*/
  if(fip==0){
    //printf("All are inphase.\n");
    end=hp;
  }
  /*If return value is -1 it means no inphase point found till 2*hp*/
  else if(fip==-1){
    //printf("Continue with 3*hp\n");
    end=3*hp;
  }
  /*if it's other than 0,-1 it means inphase point is found and we will check for minimum of two.*/
  else{
    //printf("First Inphase time is:%f\n",fip);
    end=(fip+hp)>(3*hp)?3*hp:fip+hp;
  }
  //printf("Schedule will be from 0 to %f\n",end);
  /*Will pass the control to FindSchedule module to handle the scheduling of the taskset. If it's schedulable it will return 1 else 0.*/
  if(FindSchedule(t,end,count)){
    printf("Scheduling using MLLF done.\n");
  }
  else{
    printf("Scheduling Not Done.\n");
  }
  /*Freeing the dynamic memory allocated.*/
   free(t.phase);
   free(t.p);
   free(t.d);
   free(t.c);
}
