#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "comm.h"

/* -------------------------Main function for the client ----------------------*/
void main(int argc, char * argv[]) {
	int pipe_to_user[2], pipe_to_server[2];

	// You will need to get user name as a parameter, argv[1].
	char* username = argv[1];
	if(connect_to_server("500", argv[1], pipe_to_user, pipe_to_server) == -1) {
		printf("%s","rip");
		exit(-1);
	}
	printf("Hello! You are connected.");
	/* -------------- YOUR CODE STARTS HERE -----------------------------------*/
	if (close(pipe_to_user[1]) == -1) {
		perror("Failed to close pipe to user\n");
	};
	if (close(pipe_to_server[0]) == -1) {
		perror("Failed to close pipe to server\n");
	};
	fcntl(0, F_SETFL, fcntl(0, F_GETFL)| O_NONBLOCK);
	fcntl(pipe_to_user[0], F_SETFL, fcntl(pipe_to_user[0], F_GETFL)| O_NONBLOCK);

	printf("\nPipe to read: %d\n", pipe_to_user[0]);
	printf("Pipe to write: %d\n", pipe_to_server[1]);
	print_prompt(username);
	int nbytesfromstin = 0;
	int nbytesfrompipe = 0;
	char buf[MAX_MSG];
	char buf2[MAX_MSG];
	// Signal handler for interrupt
	void handle_interrupt(int sig) {
		printf("%s\n","User interrupt");
		if(write(pipe_to_server[1],"\\exit",sizeof("\\exit")) == -1){
			perror("\nFailed to write to server");
		}
	}
	// Signal handler for segfault
	void handle_seg(int sig) {
		if(write(pipe_to_server[1],"\\exit",sizeof("\\exit")) == -1){
			perror("\nFailed to write to server");
		}
		printf("%s\n","Segmentation Fault");
		exit(-1);
	}
	signal(SIGINT,handle_interrupt);
	signal(SIGSEGV,handle_seg);
	while (1) {
		// Poll for user input to server
		nbytesfromstin = read(0,buf,sizeof(buf));
		strtok(buf, "\n");
		usleep(50);
		if (nbytesfromstin > 0) {
			if (strcmp(buf,"\\seg") == 0) {
				memset(buf,'\0',MAX_MSG);
				char *n=NULL;
				*n=1;
			}
			if(write(pipe_to_server[1],buf,sizeof(buf)) == -1){
				perror("\nFailed to write to server");
			}
			memset(buf,'\0',MAX_MSG);
			print_prompt(username);
		}
		// Poll for messages from server and print to user
		nbytesfrompipe = read(pipe_to_user[0],buf2,sizeof(buf2));
		if (nbytesfrompipe > 0) {
			printf("%s\n",buf2);
			memset(buf2,'\0',MAX_MSG);
			print_prompt(username);
		}
		usleep(200);

	}
	/* -------------- YOUR CODE ENDS HERE -----------------------------------*/
}

/*--------------------------End of main for the client --------------------------*/
