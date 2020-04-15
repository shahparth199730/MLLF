/*
    methods related to tasks such as
    1. reading taskset from file
    2. initializing taskset
    3. calculating hyperperiod
    4. calculating of the duration of schedule i.e.., 0 to min(3*hyper-period,first-in-phase time+hyperperiod)
*/
#include"scheduler.h"

int noOfTasks=0;
float hyperperiod;
void AllocateTaskSet()
{
  taskSet=(struct task*)malloc(sizeof(struct task));
}

void ReAllocateTaskSet()
{
  taskSet=(struct task*) realloc(taskSet,noOfTasks*sizeof(struct task)+sizeof(struct task));
}

bool CreateSchedule(char* fileName)
{
  //read the taskset from the file
    bool isTaskSetInitialized,res=false;
    isTaskSetInitialized=InitializeTaskSet(fileName);
    if(isTaskSetInitialized)
    {
      CalculateHyperPeriod(taskSet,noOfTasks);
      PrintHyperPeriod();
      //TODO: set the res to true of everything is correct

      res=true;
    }
    return res; 
}

bool InitializeTaskSet(char *fileName)
{
    bool res=false;
    FILE *fp;
    fp=fopen(fileName,"r");
    if(fp!=NULL)
    {
        char line[MAX];
        //read input data from the file pointer, and assign it to the task;
        AllocateTaskSet();
        while(fgets(line,MAX,fp)!=NULL) 
        {
            ReAllocateTaskSet();
            InitializeTask(line);
        }   
        PrintTaskSet();  
        res=true;
    }
    else
      printf("Could not open the given file");

    return res;
}

void InitializeTask(char* line)
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
    taskSet[noOfTasks].id=noOfTasks+1;
    taskSet[noOfTasks].phase=atof(param[0]);
    taskSet[noOfTasks].p=atof(param[1]);
    taskSet[noOfTasks].c=atof(param[2]);
    taskSet[noOfTasks].d=atof(param[3]);
    noOfTasks++;
}

void PrintTaskSet()
{
  int i;
  printf("*****************************************TASKSET****************************************\n");
  for(i=0;i<noOfTasks;i++)
  {
      printf("ID:%d\tPhase:%.2f\tPeriod:%.2f\tExecution Time:%.2f\tRelative Deadline: %.2f\n",
      taskSet[i].id,taskSet[i].phase,taskSet[i].p,taskSet[i].c,taskSet[i].d);
  }
}

float GetRandomNumber()
{
    //everytime generates a different random number within the given range
    float randomNumber;
    srand(time(0));
    randomNumber=((rand()%5)+6)/10.0;
    return randomNumber;
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


void CalculateHyperPeriod(struct task *t,int count){
  hyperperiod= findlcm(t,count);
}


void PrintHyperPeriod()
{
    printf("HyerPeriod is %.2f\n",hyperperiod);
}
