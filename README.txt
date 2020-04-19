[1] Submitted by: Group6 [Ajay Kharat-2019H1030011G,Dilpreet Kaur-2019H1030907G,Pallavi Varshney-2019H1030029G,Parth Shah-2019H1030563G]

[2] Referred: Sung-Heun Oh and Seung-Min Yang, "A Modified Least-Laxity-First scheduling algorithm for real-time tasks," Proceedings Fifth International Conference on Real-Time Computing Systems and Applications (Cat. No.98EX236), Hiroshima, Japan, 1998, pp. 31-36.

[3] List of files:
1. header.h : Contains the headerfiles required, structures, anf function declarations.
2. Driver.c : The file containg the main function which will take input from commandline and pass it to Scheduler.c
3. Scheduler.c : It will select which job to execute and return the job id back to the FindSchedule function. If there is tie int the laxity it will call the TieBreaker which will break the tie by selecting the curre job which was executing.
4. FindSchedule.c : It will create the jobs dynamically. Will start the counter from 0 and will take the jobs whose arrival is less than or equal to counter value. For every point Scheduler function will call which will select which job to be executed. At the end of the schedule will call ResponseTime and WaitingTime module to calculate response time and waiting time of different jobs in the schedule.
5. ResponseTime.c : It will find the response time and waiting time for the periodic jobs.
6. Comparator.c : It contains comparator functions definition used in quicksort
7. CreateNewJob.c : It will initialize the new job with the required parameters and return.
8. Handler.c : It will read the taskset from the given file. Check for the utilization. If it's more than 1 we will display the not schedulable message and return. If it's not more than 1, we will find the HyperPeriod followed by inphase point if any and based on that we will decide the schedule. The schedule will begin from 0 and end with minimum of 3*HyperPeriod or first inphase point+HyperPeriod.
9. Inphase.c : It will check if there's no job having phase non-zero it will return 0. Else it will try to find the inphase point if any till 2*hp(because we will take minimum of 3*hp and first inPhase+hp).
10. ResonseTime.c : It will calculate the response time of all the jobs in the taskset. Will find absolute response jitter, relative response jitter,minimum, maximum and average response time for all the tasks.
11. TieBreaker.c : It will select job which was currently executing in the tie breaker scenario.
12. WaitingTIme.c : It will calculate the waiting time of all the jobs in the taskset. Will find minimum, maximum and average waiting time for all the tasks.
13. taskset.txt : Input file containing periodic taskset.

Output Files:
1. periodicSchedule.txt : It will contain normal periodic jobs scheduling using MLLF. It also contain total number of preemptions,maximum response time,absolute response time jitter,relative response time jitter and average response time.

[3] TO COMPILE our program:
Type make in the terminal and it will compile the program.

[4] TO EXECUTE our program:
Type ./solution taskset.txt
where ./solution is executable file and taskset.txt is the input file containing taskset.

[5] Description of the structure of our program:
Initially when the program is executed by the above mention instruction from (3 and 4) the filename which is passed as argument will be received by Driver file and it will pass it to handler. Handler will find the total utilization and if it's less than 1 it will find the hyperperiod, first inphase point and based on the minimum criteria of 3*HyperPeriod or first inphase point+HyperPeriod it will select the end of the schedule. Once the parameters are found it will call the FindSchedule where initially only the first instance of each jobs are created and the counter will start for creating the schedule. We have Three decision points 1) Arrival Time of Job. 2) Termination of job. 3) If the given instance of Dmin-Laxity of current job expires. As soon as any decison criteria is met we will call the scheduler and scheduler will pick which job to execute in case of tie we will call the TieBreaker module which will select the job if it's currently which was currently running among the all. We will have 0.1 unit of decision overhead. If a old job has been preempted we will add 0.2 unit of preemption overhead. As soon as the instance of the job has been completed the new instance of job for that particular task will be created. When the arrival time becomes less than or equal to the current time we will add those jobs to ready queue. And will schedule thpse jobs. Once the schedule has been created we will print the total preemption and call ResonseTime and WaitingTime module to calculate and print the response time and waiting time of the jobs.

ASSUMPTION:
The period and the deadline of the periodic jobs are assumed to be equal.
