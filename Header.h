/* List of Header files required*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
/* Structure of the task used to handle the periodic taskset*/
struct task{
  float *phase;
  float* p;
  float* d;
  float* c;
};
/*Structure required to handle the jobs of each task*/
struct jobs{
  float phase;
  int job_id;
  int instance_id;
  float arrival;
  float deadline;
  int visit;
  float execution;
};
/*Function declarations of the various functions used in the program.*/
void Handler(char* );
float HyperPeriod(float *, int );
float Inphase(float *,float *,int,float );
