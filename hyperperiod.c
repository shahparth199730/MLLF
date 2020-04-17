#include"scheduler.h"

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


float CalculateHyperPeriod(struct task *t,int count){
  float hyperperiod;
  hyperperiod= findlcm(t,count);
  return hyperperiod;
}


void PrintHyperPeriod(float hyperperiod)
{
    printf("HyerPeriod is %.2f\n",hyperperiod);
}