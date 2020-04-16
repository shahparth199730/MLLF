#ifndef __RTS__
#define __RTS__
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define MAX 1000

/* Structure of the task used to handle the periodic taskset*/
struct task{
  int id;
  float phase;
  float p;
  float d;
  float c;
};

enum jobType
{Normal,
contextOverhead,
preemptionOverhead
};

struct job
{
  int id[3];
  float startTime;
  float endTime;
  struct task *associatedTask;
  float absoluteDeadline;
  //to identify if the job in the schedule is an overhead, like context switch and pre-emption
  //associated Task is NULL, and id=00i for i=0 to n(n-no of overheads) for such jobs
  //to identify which overhead among the overheads, we have enum datatype
  bool isOverhead;
  int jobType;
};

struct task* AllocateTaskSet(struct task*);

struct task* ReAllocateTaskSet(struct task*,int);

bool CreateSchedule(char*);

struct task* InitializeTaskSet(char*,int*);

float GetRandomNumber();

struct task* InitializeTask(struct task*,char*,int);

void PrintTaskSet(struct task*,int);

float gcd(float, float);

float findlcm(struct task*, int);

float CalculateHyperPeriod(struct task*,int);

void PrintHyperPeriod(float);

bool CheckTaskSetFeasibility(struct task*,int);

float Inphase(struct task*,int,float);

float FindScheduleEnd(float,float);

struct job* FindFeasibleSchedule(struct task*,float,int,int*);

int* FindCurrentlyActiveTasks(float*,int,float,int*);

float* CreateExecutionTimeArr(int);

void InitializeExecutionTimeArr(float*,struct task*,int);

struct job* AddOverheadJob(struct job*,int,float,int,bool);

struct job* AddOverheadToSchedule(struct job*,int*,float*,int*,bool);

int FindNextTaskToBeScheduled(int *,int ,float *,struct task *,float *,int,float*);

float* FindLaxityOfAvailableTasks(int *,int ,float ,float *);

float FindLaxity(int,float*,float);

float FindMinLaxity(float*,int);

int BreakTie(int*,int,float*,int);

float FindNextTaskArrival(struct task*,float*,float,int,float);

float FindJobDuration(int,struct task*,float*,float,int,float,float);

float FindNextTaskArrival(struct task*,float*,float,int ,float);

int FindTMIN(struct task *,int,int,float,float,float *);
#endif
