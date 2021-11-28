//**************************************************************
//	Demonstrates how to "wait" for thread completions by using the Pthread join routine.
// Threads are explicitly created in a joinable state for portability reasons.
//	Use of the pthread_exit status argument is also shown.
// Run cc -lm -o PTH_join PTH_join.c
//**************************************************************
// int pthread_create( pthread_t* thread,const pthread_attr_t* attr,
//                    void* (*start_routine)(void* ),void* arg );
// Arguments:
  // thread -> NULL, or a pointer to a pthread_t object where the function can store the thread ID of the new thread.
  // attr -> A pointer to a pthread_attr_t structure that specifies the attributes of the new thread. 
        // If attr is NULL, the default attributes are used (see pthread_attr_init()).
  // start_routine -> The routine where the thread begins, with arg as its only argument. 
  // arg -> The argument to pass to start_routine.
//**************************************************************
//int pthread_join( pthread_t thread, void** value_ptr );
// Arguments:
   // thread -> The target thread whose termination you're waiting for. (reference thread)
   // value_ptr -> NULL, or a pointer to a location where the function can store the value passed to pthread_exit() by the target thread.
// Description:
// The pthread_join() function blocks the calling thread until the reference thread terminates, unless thread has already terminated. 
// If value_ptr is non-NULL and pthread_join() returns successfully, then the value passed to pthread_exit() by the target thread is placed in value_ptr. 
// If the target thread has been canceled then value_ptr is set to PTHREAD_CANCELED.
//**************************************************************
// void pthread_exit( void* value_ptr );
// Arguments:
   // value_ptr -> A pointer to a value that you want to be made available to any thread joining the thread that you're terminating.
// Description: 
//The pthread_exit() function terminates the calling thread. 
// If the thread is joinable, the value value_ptr is made available to any thread joining the terminating thread  
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4

void *BusyWork(void *t)
{
   int i;
   long tid;
   double result = 0.0;
   tid = (long)t;
   printf("Thread %ld starting...\n", tid);
   for (i = 0; i < 1000000; i++)
   // take long time work 
   {
      result = result + sin(i) * tan(i);
   }
   printf("Thread %ld done. Result = %e\n", tid, result);
   pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
   pthread_t thread[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   void *status;

   // Initialize and set thread detached attribute  
   pthread_attr_init(&attr);
   // change thread attribute to be joinable 
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for (t = 0; t < NUM_THREADS; t++)
   {
      printf("Main: creating thread %ld\n", t);
      rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   // Free attribute and wait for the other threads */
   // destroys the given thread-attribute object.
   pthread_attr_destroy(&attr);

   for (t = 0; t < NUM_THREADS; t++)
   {
      // suspend the execution of the calling thread until the reference thread terminates 
      rc = pthread_join(thread[t], &status);
      if (rc)
      {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
      }
      printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
   }

   // Main thread will wait for all thread to complete then terminated
   printf("Main: program completed. Exiting.\n");
   pthread_exit(NULL);
}
