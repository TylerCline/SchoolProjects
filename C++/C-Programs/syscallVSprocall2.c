#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>


long nanoseconds(struct timeval t)
{ 
  
  long x = t.tv_sec*1000000+t.tv_usec;
  long y = 1000;
  return(x*y);

}
main()
{
  int i, cntr,average;
  long N = 1000000;
  float syscallAverage, procCallAverage;
  struct timeval t1, t2;
  average = gettimeofday(&t1, NULL);

  i = 0;
  while(i < N)
  {
    cntr = getpid();
    i++;
  }

  average = gettimeofday(&t2, NULL);   
  syscallAverage = (nanoseconds(t2) - nanoseconds(t1))/(N*1.0);
  average = gettimeofday(&t1,NULL);  

  i = 0;
  while(i < N)
  {
    cntr = 10;
    i++;
  }

  average = gettimeofday(&t2, NULL); 
  procCallAverage = (nanoseconds(t2) - nanoseconds(t1))/(N*1.0);
  printf("System call: %f\n", syscallAverage);
  printf("Procedurecall : %f\n", procCallAverage);
}

