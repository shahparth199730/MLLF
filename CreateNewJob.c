void CreateNewJob(struct jobs* job,struct task t,int *k,int curr_job){
  job[*k].job_id=job[curr_job].job_id;
  job[*k].instance_id=job[curr_job].instance_id+1;
  job[*k].arrival=job[curr_job].arrival+t.p[job[curr_job].job_id-1];
  job[*k].deadline=job[*k].arrival+t.d[job[curr_job].job_id-1];
  job[*k].execution=t.c[job[curr_job].job_id-1];
  job[*k].visit=0;
  job[*k].finish=0;
  printf("J%d,%d with execution:%f,arrival:%f,deadline:%f\n",job[*k].job_id,job[*k].instance_id,job[*k].execution,job[*k].arrival,job[*k].deadline);
  (*k)++;
}
