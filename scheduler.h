#ifndef __RTS__
#define __RTS__
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define MAX 1000

/* Structure of the task used to handle the periodic taskset*/
struct task{
  int id;
  float phase;
  float p;
  float d;
  float c;
};

struct job
{
  int id[3];
  float startTime;
  float endTime;
  struct task *associatedTask;
  float absoluteDeadline;
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

struct job* FindFeasibleSchedule(struct task*,int,int*);

int* FindCurrentlyActiveTasks(float*,int,float,int*);

float* CreateExecutionTimeArr(int);

void InitializeExecutionTimeArr(float*,struct task*,int);
#endif
