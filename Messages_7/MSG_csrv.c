//****************************************************************************************
// A combination of techniques and functions related to message send, receive and reply.
// - Establish a client/server model
// 
//	Procedures:
//	open the first terminal
//	cc -o MSG_csrv MSG_csrv ----> compile the code first 
//	1) "./MSG_csrv -s &" -----> setup server: name_attach to "myserver", MsgReceive
//	2) "./MSG_csrv -c &" -----> setup client:	name_open, Msg Send, MsgReply
//	open another terminal 
//	pidin -p MSG_csrv
//	open file manager and go to dev/name/local, see this folder appear to store name space 
//	kill pidNumber or slay MSG_csrv to stop the process 
//**************************************************************************************** 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
//**************************************************************************************** 
// Server side of the code 
//**************************************************************************************** 
int server() {
  name_attach_t *attach;
  char msg[30];
  int rcvid;
  
  //*****************				
  // name_attach() registers a name "my server" in the namespace and creates the channel
  if((attach=name_attach(NULL,"myserver",0))==NULL) {
		// Create a local name (/dev/name/local/...) 
  	// returns a pointer " *attach " to  name_attach_t structure
     printf("Error: failed to attach myserver\n");
     return EXIT_FAILURE;
 		// ensure value received by name_attach is not NULL
   }
   //*****************
  // Process MsgReceive's here now with the chid */
  while (1) {
    printf("Server Waiting\n");
    rcvid = MsgReceive(attach->chid, &msg,sizeof(msg), NULL);
     // returns the channel ID that send the message (client)
    																				
    if (rcvid == -1) 
    {	// Error condition, exit			
    break;
   }
   
   //*****************
   if (rcvid>0) {				
     // Test for nature of message received
     printf("Server Received Message:  %s \n", msg);
     MsgReply(rcvid, EOK, 0, 0);
		// EOK here a constant value = 0 
     }
   }  						
    //*****************
// Remove the name from the space and destroy the channel 
name_detach(attach, 0);
return EXIT_SUCCESS;
}
//************************************************************************************
// Client Side of the code
//************************************************************************************
int client() {
  char msg[30];
  int fd;
  int count=0;

  //*****************
  if((fd = name_open("myserver", 0)) ==-1) {
		// return the handler to the channel so that can write to the server 
    // open a name for a server connection
      return EXIT_FAILURE;
    }
  printf("Client Sending %d \n", msg);

   //*****************
  while(1) {    					
    // Do work with server connection
    sprintf(msg,"\nPlease Reply: %4x(Hex)\n", count);
    if (MsgSend(fd, &msg, sizeof(msg), NULL, 0) == -1) 
      break;
	  ++count;
	  delay(500);
  }
	// Close the connection */
  name_close(fd);
  return EXIT_SUCCESS;
}
//***********************************************************************************
// The main function - allow eash housekeeping
// - one program two processes by using "-s" or "-c"argument passing 
//***********************************************************************************
int main(int argc, char **argv) {
int ret;

if (argc < 2) {
  printf("Usage %s -s | -c \n", argv[0]);
  ret = EXIT_FAILURE;
 }
else if (strcmp(argv[1], "-c") == 0) {
     printf("Running Client ... \n");
     ret = client();   							
    }
else if (strcmp(argv[1], "-s") == 0) {
     printf("Running Server ... \n");
     ret = server();   
 }
 else {
        printf("Usage %s -s | -c \n", argv[0]);
        ret = EXIT_FAILURE;
 }
 return ret;
 }
 
 