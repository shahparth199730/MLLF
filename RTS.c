#include<stdio.h>
#include<stdlib.h>

#define Periodic_COL 4

#define sporadic_COL 3

#define aperiodic_COL 2

// Find GCD using euclidien method
int gcd(int x, int y) 
{ 
    if (y == 0) 
        return x; 
    return gcd(y, x % y); 
} 
  
// Find LCM of array elements 
int findlcm(int *arr, int n) 
{ 

    int res = *(arr+0); 
 
    for (int i = 1; i < n; i++) 
    {
    res = (((arr[i] * res)) / (gcd(arr[i], res))); 
    }
  
    return res; 
} 


int main(int argc, char * argv[])
{

//////////////////////////
//Periodic Filepointer///
/////////////////////////
FILE *fp;
 
//Per_taskfname hold input file address
char * ptaskfname= argv[1];

int i,j,n;

char c1;
int count1=0;

if (argc < 2)
{
 printf("Please enter filename \n");
 return 1;
}


fp = fopen(ptaskfname, "r"); 

if (fp == NULL) 	        
{ 
printf("File %s not found \n", ptaskfname); 
exit(0); 
} 

//Count no. of lines in a inputPeriodic.txt file
for (c1 = getc(fp); c1 != EOF; c1 = getc(fp)) 
        if (c1 == '\n')  
         count1 = count1 + 1; 

//Move contol back to top of file
rewind(fp);
  
//Displaying Count of Periodic tasket in input file
printf("No. of PERIODIC Taskset %d \n",count1);

const int const Periodic_ROW = count1;

int taskset[Periodic_ROW][Periodic_COL];
int phase[Periodic_ROW];
int period[Periodic_ROW];
int wcet[Periodic_ROW];
int rdead[Periodic_ROW];

//Reading periodic taskset from file 
for(i=0;i<Periodic_ROW;i++)
{
for(j=0;j<Periodic_COL;j++)
{
fscanf(fp,"%d",&n);
taskset[i][j]=n;
if(j==0)
phase[i]=n;
else if(j==1)
period[i]=n;
else if(j==2)
wcet[i]=n;
else if(j==3)
rdead[i]=n;

//printf("%d\t",n);
}
//printf("\n");
}


//Displaying tasket on console
for(i=0;i<Periodic_ROW;i++)
{
for(j=0;j<Periodic_COL;j++)
{
if(j==0)
printf("%d\t",phase[i]);
else if(j==1)
printf("%d\t",period[i]);
else if(j==2)
printf("%d\t",wcet[i]);
else if(j==3)
printf("%d\t",rdead[i]);
}
printf("\n");
}

//FINDING HyperPeriod using LCM={period[i]}
int psize = sizeof(period) / sizeof(period[0]); 
int H = findlcm(period, psize);
printf("Hyperiod = %d \n",H); 


//FINDING Schedule length
//First in-phase time + HyperPeriod

int inPhase;

int  ** inPhase = calloc(sizeof(*array), Periodic_ROW);
for(i=0;i<Periodic_ROW;i++)
{
int n_jobs = H/period[i];
inPhase[i] = calloc(sizeof(**inPhase), n_jobs ); // No. of Jobs in each tasks
printf("No of Jobs in Task %dth Task = %d \n",(i+1),n_jobs); 
inPhase[i][0] = phase[i];
for(j=1;j<=n_jobs;j++)
{
inPhase[i][j] = inPhase[i][j-1] + period[i];
printf("%d\t",inPhase[i][j-1]);
}
printf("\n");

}



fclose(fp);


return 0;
}
