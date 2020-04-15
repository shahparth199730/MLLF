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

struct task *taskSet;
extern int noOfTasks;
extern float hyperperiod;

void AllocateTaskSet();

void ReAllocateTaskSet();

bool CreateSchedule(char*);

bool InitializeTaskSet(char*);

float GetRandomNumber();

void InitializeTask(char*);

void PrintTaskSet();

float gcd(float, float);

float findlcm(struct task*, int);

void CalculateHyperPeriod(struct task*,int);

void PrintHyperPeriod();

bool CheckTaskSetFeasibility();
#endif
