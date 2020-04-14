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
return num;
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
