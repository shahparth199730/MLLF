/* List of Header files required*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<limits.h>
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
  float finish;
};
struct laxity{
  float slack;
  int id;
  float execution;
};
/*Function declarations of the various functions used in the program.*/
void Handler(char* );
float HyperPeriod(float *, int );
float Inphase(float *,float *,int,float );
int FindSchedule(struct task,float,int);
void Scheduler(float ,struct jobs* ,int ,int,float *,int*);
void TieBreaker(struct jobs *,struct laxity *,int ,int,float*,int*);
