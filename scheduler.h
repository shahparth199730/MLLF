#ifndef __RTS__
#define __RTS__
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

struct periodicTask{            		 //task definition
	int phase,p,D,id;           		 //following standard naming convention  
	float c;                 		//p=period,D=realtive deadline,c=execution time  
};

struct periodicJob{                         	//job definition
  	int arr_time,deadline,id;       		//arr_time=arrival time   
  	float wcet;
};

struct slack{
  float val;
  int id;
};

int readFile(FILE**);
struct periodicTask* readPeriodicTaskSet(FILE*,int);
bool checkFeasibility(struct periodicTask *t,int n);
int calcHyperPeriod(struct periodicTask*,int);
// void calculateSlack(struct periodicTask*,int,int);
// void buildMinHeap(struct slack [],int);
// void minHeapify(struct slack [],int ,int );
#endif
