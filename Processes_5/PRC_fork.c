//*****************************************************************************
// 	Demonstrates a more sophisticated fork process, 
//  how the parent & child process can be identified.
//
// 	A duplicate process is created with same data, executes at the point of
// 	creation also highlights independent memory.
//
//	New functions: pid_t fork(); sleep(unsigned int seconds)
// return value of folk: 
// child process -- 0; The process ID of the child process to the parent process. 
// Both processes continue to execute from the fork() function. 
// If an error occurs, fork() returns -1 to the parent and sets errno.
//*****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <process.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid, child_pid;
  int shmem = 999;
  int ownmem = 888;

  printf("This is the parent process : pid = %d\n\n", getpid());
  sleep(1);

  if (child_pid = fork()) 
  {
    for (;;)
    {
      printf("This is the parent : child pid is %d shmem is %d ownmem is %d\n",
             child_pid, shmem, ownmem);
      ownmem -= 1;
      sleep(1);
    }
  }
  else
  {
    for (;;)
    {
      printf("This is the child : pid is %d shmem = %d ownmem = %d\n",
             child_pid, shmem, ownmem);
      ownmem += 1;
      sleep(1);
    }
  }
  return (EXIT_SUCCESS);
}
