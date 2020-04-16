/*
    methods related to tasks such as
    1. reading taskset from file
    2. initializing taskset
    3. calculating hyperperiod
    4. calculating of the duration of schedule i.e.., 0 to min(3*hyper-period,first-in-phase time+hyperperiod)
*/
#include"scheduler.h"

struct task* AllocateTaskSet(struct task* taskSet)
{
  taskSet=(struct task*)malloc(sizeof(struct task));
  return taskSet;
}

struct task* ReAllocateTaskSet(struct task* taskSet,int noOfTasks)
{
  taskSet=(struct task*) realloc(taskSet,noOfTasks*sizeof(struct task)+sizeof(struct task));
  return taskSet;
}

bool CreateSchedule(char* fileName)
{
  //read the taskset from the file
    bool res=false;
    int noOfTasks=0,*count,noOfJobs,*jobCount;
    count=&noOfTasks;
    struct task *taskSet=InitializeTaskSet(fileName,count);
    float hyperperiod,inPhaseTime,start=0.0,end;
    struct job *schedule;
    jobCount=&noOfJobs;
    PrintTaskSet(taskSet,*count);
    if(CheckTaskSetFeasibility(taskSet,noOfTasks))
    {
      hyperperiod=CalculateHyperPeriod(taskSet,*count);
      PrintHyperPeriod(hyperperiod);
      inPhaseTime=Inphase(taskSet, *count,hyperperiod);
      end=FindScheduleEnd(inPhaseTime,hyperperiod);
      schedule=FindFeasibleSchedule(taskSet,noOfTasks,jobCount);
      res=true;
    }
    return res; 
}

struct task* InitializeTaskSet(char *fileName,int* count)
{
    FILE *fp;
    struct task *taskSet;
    fp=fopen(fileName,"r");
    if(fp!=NULL)
    {
        char line[MAX];
        //read input data from the file pointer, and assign it to the task;
        taskSet=AllocateTaskSet(taskSet);
        while(fgets(line,MAX,fp)!=NULL) 
        {
            taskSet=InitializeTask(taskSet,line,*count);
            (*count)++;
            taskSet=ReAllocateTaskSet(taskSet,*count);
        }   
    }
    else
      printf("Could not open the given file");

    fclose(fp);
    return taskSet;
}

struct task* InitializeTask(struct task* taskSet,char* line,int count)
{ 
    //read each line and set the parameters for the taskset
    char* token=strtok(line,",");
    char *param[4];
    int i=0;
    while(token!=NULL)
    {
        param[i++]=token;
        token=strtok(NULL,",");   
    }
    taskSet[count].id=count+1;
    taskSet[count].phase=atof(param[0]);
    taskSet[count].p=atof(param[1]);
    taskSet[count].c=atof(param[2]);
    taskSet[count].d=atof(param[3]);
    return taskSet;
}

void PrintTaskSet(struct task *taskSet,int noOfTasks)
{
  int i;
  printf("*****************************************TASKSET****************************************\n");
  for(i=0;i<noOfTasks;i++)
  {
      printf("ID:%d\tPhase:%.2f\tPeriod:%.2f\tExecution Time:%.2f\tRelative Deadline: %.2f\n",
      taskSet[i].id,taskSet[i].phase,taskSet[i].p,taskSet[i].c,taskSet[i].d);
  }
}

/* It will find the hyperperiod by using gcd and lcm functions and as per the formula of finding hyperperiod. */
/* gcd is helping function for finding lcm*/
float gcd(float a, float b)
{
    // if (b == 0)
    //     return a;
    // return gcd(b, fmod(a, b));
    if (a < b)
        return gcd(b, a);

    // base case
    if (fabs(b) < 0.001)
        return a;

    else
        return (gcd(b, a - floor(a / b) * b));
}

/* findlcm will find the lcm of all the periods and return its value.*/
float findlcm(struct task arr[], int n)
{
    float ans = arr[0].p;
    for (int i = 1; i < n; i++){
        float temp=(gcd(arr[i].p, ans));
        ans = (((arr[i].p * ans)) / temp);
    }
    return ans;
}


float CalculateHyperPeriod(struct task *t,int count){
  float hyperperiod;
  hyperperiod= findlcm(t,count);
  return hyperperiod;
}


void PrintHyperPeriod(float hyperperiod)
{
    printf("HyerPeriod is %.2f\n",hyperperiod);
}

bool CheckTaskSetFeasibility(struct task *taskSet,int noOfTasks)
{
  int i;
  float utilization=0;
  for(int i=0;i<noOfTasks;i++){
      utilization+=(taskSet[i].c/taskSet[i].p);
  }
  return (utilization<=1);
}

float Inphase(struct task *taskSet, int count,float hp){
  int *x=(int *)malloc(count*sizeof(int));
  float max=0.0;
  int id=-1;
  int flag=0;
  for(int i=0;i<count;i++){
    x[i]=0;
    if(taskSet[i].phase!=0){
      flag=1;
    }
    if(max<taskSet[i].p){
      max=taskSet[i].p;
      id=i;
    }
  }
  if(flag==0){
    return 0;
  }
  float inPhase=-1;
  float  ** array = calloc(sizeof(*array), count);
  for(int i=0;i<count;i++)
  {
  int n_jobs = (3*hp)/taskSet[i].p;
  array[i] = calloc(sizeof(**array), n_jobs+1 ); 
  array[i][0] = taskSet[i].phase;
  for(int j=1;j<=n_jobs;j++)
  {
  array[i][j] = array[i][j-1] + taskSet[i].p;
  }
  }
  for( ; x[id] <= (3*hp)/taskSet[id].p; x[id]++ ) {
        float val = array[id][x[id]];
        int print = 1;
        for( int i = 0; i < count; i++ ) {
          if(i==id){
            continue;
          }
            while (x[i] <= (3*hp)/taskSet[i].p && array[i][x[i]] < val ) {
              x[i]++;
            }
            if (array[i][x[i]] != val) print = 0;
        }
        if (print==1){
          inPhase=val;
          break;
        }
    }
    free(x);
    free(array);
  return inPhase;
}


float FindScheduleEnd(float inPhaseTime,float hyperperiod)
{
    float end;
    if(inPhaseTime==0)
    {
    end=3*hyperperiod;
    }
    else if(inPhaseTime==-1)
    {
      end=3*hyperperiod;
    }
    else
    {
      end=(inPhaseTime+hyperperiod)>(3*hyperperiod)?3*hyperperiod:inPhaseTime+hyperperiod;
    }
  return end;
}