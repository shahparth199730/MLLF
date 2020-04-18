/******************************************************************************************************************
It will find the hyperperiod by using gcd and lcm functions and as per the formula of finding hyperperiod.
******************************************************************************************************************/
/* gcd is helping function for finding lcm*/
float gcd(float a, float b)
{
    if(a < b){
      return gcd(b, a);
    }
    if(fabs(b) < 0.001){
      return a;
    }
    else{
      return (gcd(b, a - floor(a / b) * b));
    }
}
/* findlcm will find the lcm of all the periods and return its value.*/
float findlcm(float arr[], int n)
{
    float ans = arr[0];
    for (int i = 1; i < n; i++){
        //printf("ans:%f befor i:%f\n",ans,arr[i]);
        float temp=(gcd(arr[i], ans));
        ans = (((arr[i] * ans)) / temp);
        //printf("gcd:%f before i:%f\n",temp,arr[i]);
    }
    return ans;
}
float HyperPeriod(float *p,int count){
  return findlcm(p,count);
}
