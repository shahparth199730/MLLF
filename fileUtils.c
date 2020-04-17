#include"scheduler.h"

/**
    this file contains methods related to the 
    1. reading from file
*/

struct task* InitializeTaskSet(char *fileName,int* count)
{
    FILE *fp;
    struct task *taskSet=NULL;
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