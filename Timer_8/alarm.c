#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// ***************
void alarm_handler( int signum ) {
  printf( "\nSignal raised.\n" );
	//when the signal received, branching would move to this handler and complete
  }
//**************
int main( void ) {
  unsigned int timeleft;
  int rtn;
  signal( SIGALRM, alarm_handler ); 	 
  //associate sigalarm to the alarm handler 
  //**************
  printf("Set the alarm and sleep\n" );
  alarm(5);
  sleep( 2 ); 		//Sleep for 2 seconds
  timeleft = alarm( 0 );
		 //cancel alarm
  printf( "Time left before cancel, and rearm: %d\n", timeleft ); 
	// Why the outcome here is 2 instead of 3. set alarm in 5s and sleep for 2 second, should left 3s 
 	//because (scheduler policy), u always sleep longer than u inspect. resolution 
  //**************
  alarm( timeleft ); 	// set an alarm to go off again
  printf("Hang around, waiting to return in %d secs\n", timeleft );
  //**************
  rtn = pause();      	// suspend process until delivery of signal
  printf( "Pause returned with %d.  Sleep for 5 secs\n", rtn );//-1
  //**************
  alarm( 2 );
  rtn = sleep(5);
  printf( "Returned from sleep, only slept %d secs\n", 5-rtn );
  return 0;
}
