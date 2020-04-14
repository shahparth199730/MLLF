/*
    methods related to tasks such as
    1. reading taskset from file
    2. initializing taskset
    3. calculating hyperperiod
    4. calculating of the duration of schedule i.e.., 0 to min(3*hyper-period,first-in-phase time+hyperperiod)
*/
#include"scheduler.h"

int readFile(FILE **f){
 int i,num=0;
 char file_name[80],ch;
 printf("\nEnter file name: ");
 scanf("%s",file_name);
 *f = fopen(file_name, "r");
  if (*f == NULL) { 
	printf("Error opening file\n");
	exit(0);
  }
 while((ch=fgetc(*f))!='\n')
    num = num*10 + (ch-48);

printf("num is %d",num);
return num;
}


///read the periodic taskset from file///
struct periodicTask* readPeriodicTaskSet(FILE* f,int n){
 struct periodicTask* per_tsk=(struct periodicTask*)calloc(n,sizeof(struct periodicTask));
 int i;
 printf("\n***************PERIODIC TASK SET*************************\n");
  if(per_tsk==NULL){
	printf("Memory not allocated");
	exit(0);
  }
  for (i = 0; i < n; i++) {
     fscanf(f, "%d %d %f", &per_tsk[i].phase,&per_tsk[i].p,&per_tsk[i].c);
     per_tsk[i].id=i;
     per_tsk[i].D=per_tsk[i].p;
     printf("%d %.1f %d\n",per_tsk[i].p,per_tsk[i].c,per_tsk[i].D);
  }
  fclose(f);
 return per_tsk;
}


int gcd(int a,int b) {
  if(a == b)     return a;
  else if(a>b) return gcd(a-b,b)	;
  else 	       return gcd(a,b-a);
}

int calcHyperPeriod(struct periodicTask *t,int n){ 
  int hcf,lcm,a,b;
  a = t[0].p;
  b = t[1].p;
  hcf = gcd(a,b);
  lcm = (a*b)/hcf;
 // printf("t=%ld t[0]=%ld\n",sizeof(*t),sizeof(t[0]));
  for(int i=2;i<n;i++){
    a = lcm;
    b = t[i].p;
    hcf = gcd(a,b);
    lcm = (a*b)/hcf;
  }
  printf("Hyperperiod=%d\n",lcm);
return lcm;
}

bool checkFeasibility(struct periodicTask *t,int n){
  float u=0;
  bool res=true;
  int i;
  for(i=0;i<n;i++)
    u+=t[i].c/(t[i].p<t[i].D?t[i].p:t[i].D);
  if(u>1){
    res=false;
  }
  return res;
}

