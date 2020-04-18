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

void FindFeasibleSchedule(struct task*,float,int,int*);

int* FindCurrentlyActiveTasks(float*,int,float,int*);

float* CreateExecutionTimeArr(int);

void InitializeExecutionTimeArr(float*,struct task*,int);

int FindNextTaskToBeScheduled(int *,int ,float,struct task *,float *,int,float*);

float* FindLaxityOfAvailableTasks(int *,struct task *,int ,float ,float *);

float FindLaxity(struct task *,int,float*,float);

float FindMinLaxity(float*,int);

int BreakTie(int*,int,float*,int);

float FindNextTaskArrival(struct task*,float*,float,int,float);

float FindJobDuration(int,struct task*,float*,float,int,float,float);

float FindNextTaskArrival(struct task*,float*,float,int ,float);

int FindTMIN(struct task *,int,int,float,float,float *);

void ResetNextJob(struct task *,float *,int );

float getNextJobArrivalTime(float*,float,int);

void WriteJobToFile(float,float,int,int,bool);

void WriteOverHeadToFile(float,bool);

#endif
