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
#endif
