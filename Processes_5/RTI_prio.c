//***********************************************************************
//	Demonstration of priority, scheduling & sleep
//  sched_getparam(0, &param);
//  sched_getscheduler( pid_t pid );
// 	sched_setscheduler (0, SCHED_FIFO, &param);
//***********************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <process.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char *argv[])
{
	struct sched_param params;
	int policy;
	// Get Existing Setting
	printf("\fScheduled Parameters\n");
	printf("\nPolicy Constant : <SCHED_FIFO:%d><SCHED_RR%d><SCHED_OTHER:%d>\n",
		   SCHED_FIFO, SCHED_RR, SCHED_OTHER);

	// Gets the current Priority for a process (POSIX)
	sched_getparam(0, &params);
	printf("The assigned priority is %d. and the current priority is %d\n",
		   params.sched_priority, params.sched_curpriority);
	// Required prority is received in the field of sched_priority and sched_curpriority

	// Gets the current scheduling policy for a process (POSIX)
	policy = sched_getscheduler(0);
	printf("The assigned scheduler policy is %d\n", policy);

	// Change settings & Get Net Settings
	printf("\n\nChanged Scheduled Parameters\n");
	params.sched_priority += 1;
	// increase scheduled priority

	// sets priority & scheduler policy
	sched_setscheduler(0, 2, &params);
	// -> pid_t pid ->ID of the process whose priority and scheduling policy you want to set,
	// or zero if you want to set them for the current process.
	// -> int policy, -> FIFO or Round robin
	// -> const struct sched_param *param  ->A pointer to a sched_param structure
	// whose sched_priority member holds the priority that you want to get and update.

	// Gets the current Priority for a process (POSIX)
	sched_getparam(0, &params);
	printf("The assigned priority is %d. and the current priority is %d\n",
		   params.sched_priority, params.sched_curpriority);
	// Required prority is received in the field of sched_priority and sched_curpriority

	// Gets the current scheduling policy for a process (POSIX)
	policy = sched_getscheduler(0);
	printf("The assigned scheduler policy is %d\n", policy);

	return (EXIT_SUCCESS);
}
