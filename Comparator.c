int Comparator(const void *p, const void *q)
{
    struct laxity* l1 = (struct laxity *)p;
    struct laxity* r1 = (struct laxity *)q;
    float l=l1->slack;
    float r=r1->slack;
    if(l-r>0){
      return 1;
    }
    else if(l-r==0){
      float temp1=((struct laxity *)p)->execution;
      float temp2=((struct laxity *)q)->execution;
      if(temp1<temp2){
        return -1;
      }
      else{
        return 1;
      }
    }
    else{
      return -1;
    }
    return -1;
}
