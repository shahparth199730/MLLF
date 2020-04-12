#include"myheader.h"

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
return num;
}

struct periodicTask* readPeriodicJob(FILE* f,int n){
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

void checkFeas(struct periodicTask *t,int n){
  float u=0;
  int i;
  for(i=0;i<n;i++)
    u+=t[i].c/(t[i].p<t[i].D?t[i].p:t[i].D);
  if(u>1){
     printf("\nUnfortunately...Task set is un-schedulable\n"); 
     exit(0);
  }
  printf("\nCongratulations!!! Task set is schedulable\n");
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

void calculateSlack(struct periodicTask* t,int n,int timer){
  int i;
  struct slack* s=(struct slack*)calloc(n,sizeof(struct slack));  
  for(i=0;i<n;i++){                           //calculate slack for each task
    s[i].val = t[i].D-timer-t[i].c;
    s[i].id = t[i].id;
  }
  buildMinHeap(s,n);                         //create min heap on slack
  printf("\nJob with least slack is:\n");
  for(i=0;i<n;i++)
    if(t[i].id== s[0].id){                     //display task parameters with least slack
	printf("slack=%.1f phase=%d period=%d deadline=%d execution=%.1f\n",s[0].val,t[i].phase,t[i].p,t[i].D,t[i].c);
        break;
    }
}

void buildMinHeap(struct slack slck[],int n){
 int heap_size=n-1,i;
   for(i=n/2;i>=0;i--){
     minHeapify(slck, i, heap_size);
   }
}

void minHeapify(struct slack slck[],int i,int heap_size){	//pull least slack job
 int l=2*i+1,r=2*i+2,smallest;
 struct slack temp;
  if(l<=heap_size && (slck[l].val<slck[i].val))
    smallest = l;
  else smallest = i;
  if(r<=heap_size && (slck[r].val<slck[smallest].val))
    smallest = r;
  if(smallest != i){
     temp = slck[i];
     slck[i] = slck[smallest];
     slck[smallest] = temp;
     minHeapify(slck,smallest,heap_size);
  }
}
