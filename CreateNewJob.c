/******************************************************************************************************************
This will just initialize the new job with the required parameters and return.
******************************************************************************************************************/
void CreateNewJob(struct jobs* job,struct task t,int *k,int curr_job){
  job[*k].job_id=job[curr_job].job_id;
  job[*k].instance_id=job[curr_job].instance_id+1;
  job[*k].arrival=job[curr_job].arrival+t.p[job[curr_job].job_id-1];
  job[*k].deadline=job[*k].arrival+t.d[job[curr_job].job_id-1];
  srand(time(0));
  float random=rand()%5;
  float value=((5+random)/10);
  float normalize=(float)((int)((t.c[job[curr_job].job_id-1]*value) * 100 + .5))/100;
  job[*k].execution=normalize;
  job[*k].curr_execution=job[*k].execution;
  job[*k].visit=0;
  job[*k].finish=0;
  //printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[*k].job_id,job[*k].instance_id,job[*k].execution,job[*k].arrival,job[*k].deadline);
  (*k)++;
}
