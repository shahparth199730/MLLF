#include"scheduler.h"

int main(int argc, char *argv[])
{
   if(argc>=2)
   {
      CreateSchedule(argv[1]);
   }
   else
      printf("Please enter the input file name");
   
   return 0;
}
