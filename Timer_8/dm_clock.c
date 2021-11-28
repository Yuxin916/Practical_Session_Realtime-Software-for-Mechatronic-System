//**************************************************************
//	Program : dm_clock.c
//	Demonstrates clock functions : Posix 1003.4
// 	clock_getres,clock_gettime
//********************** Hearders********************************
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
//********************** Constants********************************
#define BILLION 1000000000L
#define MILLION 1000000L
#define THOUSAND 1000L
// constant defined here all long format

int main()
{
  struct timespec res, start, stop;
  double accum;

  // get current UTC value and stored in the stucture "start"

  if (clock_gettime(CLOCK_REALTIME, &start) == -1)
  {
    perror("clock gettime");
    exit(EXIT_FAILURE);
  }

  // get current tiksize (resolution) value and stored in the stucture "res"
  if (clock_getres(CLOCK_REALTIME, &res) == -1)
  {
    perror("clock get resolution");
    exit(EXIT_FAILURE);
  }

  // Delay and print resolution
  because it is almost 0 delay(100);
  printf("Resolution is %ld micro seconds.\n", res.tv_nsec / THOUSAND);
  printf("Resolution is %ld milli seconds.\n", res.tv_nsec / MILLION);

  // get current UTC value and stored in the stucture "stop"
  if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
  {
    perror("clock gettime");
    exit(EXIT_FAILURE);
  }

  // calculate the time period
  accum = (double)(stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / BILLION;

  //print
  printf("Timings for clock_start  was : %10ld\n", start.tv_nsec);
  printf("Timings for clock_stop   was : %10ld\n", stop.tv_nsec);
  printf("Timings for clock_getres was : %9.8lf\n", accum);

  exit(EXIT_SUCCESS);
}
