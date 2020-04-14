void TieBreaker(struct jobs *job,struct laxity *l,int i,int previd,float *min_deadline,int *min_id){
  if(l[i].id==previd&&previd!=-1){
    struct laxity temp=l[0];
    l[0]=l[i];
    l[i]=temp;
  }
  *min_deadline=job[l[0].id].deadline;
  *min_id=l[0].id;
  for(int j=1;j<=i;j++){
    if(*min_deadline>job[l[j].id].deadline){
      *min_deadline=job[l[0].id].deadline;
      *min_id=l[j].id;
    }
  }
  return ;
}
