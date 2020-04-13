
#include"HyperPeriod.c"
#include"Inphase.c"
void Scheduler(char *filename){
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
  t.phase=(float *)malloc(count*sizeof(float));
  t.p=(float *)malloc(count*sizeof(float));
  t.d=(float *)malloc(count*sizeof(float));
  t.c=(float *)malloc(count*sizeof(float));
  /* Reading the taskset from the given file.*/
  while (fscanf(fp2, "%f,%f,%f,%f\n",&t.phase[i],&t.p[i], &t.c[i], &t.d[i])==4) {
        printf("%f,%f,%.1f,%f\n", t.phase[i],t.p[i], t.c[i], t.d[i]);
        i++;
  }
  fclose( fp2 );
  /*Finding the utilization */
  for(int i=0;i<count;i++){
      utilization+=(t.c[i]/t.p[i]);
  }
  if(utilization>1.0){
    printf("utilization:%f so not scheduleable.\n",utilization);
  }
    hp=HyperPeriod(t.p,count);
    printf("hp is: %f\n",hp);
    float fip=Inphase(t.phase,t.p,count,hp);
    float end=0;
    if(fip==0){
      printf("All are inphase.\n");
      end=3*hp;
    }
    else if(fip==-1){
      printf("Continue with 3*hp\n");
      end=3*hp;
    }
    else{
      printf("First Inphase time is:%f\n",fip);
      end=(fip+hp)>(3*hp)?3*hp:fip+hp;
    }
    printf("Schedule will be from 0 to %f\n",end);
     free(t.phase);
     free(t.p);
     free(t.d);
     free(t.c);
}
