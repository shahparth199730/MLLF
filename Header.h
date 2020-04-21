/******************************************************************************************************************
 List of Header files required, Structure declarations,and function declarations.
******************************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include<time.h>
/* Structure of the task used to handle the periodic taskset*/
struct task{
  float *phase;
  float* p;
  float* d;
  float* c;
};
/*Structure required to handle the jobs of each task*/
struct jobs{
  int job_id;
  int instance_id;
  float arrival;
  float deadline;
  int visit;
  float execution;
  float curr_execution;
  float finish;
};
/*Structure required to handle the laxity of each job*/
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
void CreateNewJob(struct jobs*,struct task ,int *,int);
void Scheduler(float ,struct jobs* ,int,float *,struct laxity*);
void TieBreaker(struct jobs *,struct laxity *,int ,int,float*,int*);
void ResponseTime(struct jobs*,struct task,FILE *,int,float);
void WaitingTime(struct jobs*,struct task,FILE *,int,float);
