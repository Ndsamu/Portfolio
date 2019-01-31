#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "comm.h"
#include "util.h"

/* -----------Functions that implement server functionality -------------------------*/

/*
 * Returns the empty slot on success, or -1 on failure
 */
int find_empty_slot(USER * user_list) {
	/*
   * Iterate through the user_list and check m_status to see if any slot is EMPTY
	 * Return the index of the empty slot
   */
    int i = 0;
	for(i=0;i<MAX_USER;i++) {
    	if(user_list[i].m_status == SLOT_EMPTY) {
			return i;
		}
	}
	return -1;
}

/*
 * List the existing users on the server shell
 */
int list_users(int idx, USER * user_list)
{
	/*
   * Iterate through the user list
	 * If you find any slot which is not empty, print that m_user_id
	 * If every slot is empty, print "<no users>""
	 * If the function is called by the server (that is, idx is -1), then printf the list
	 * If the function is called by the user, then send the list to the user using write() and passing m_fd_to_user
	 * Return 0 on success
   */
	int i, flag = 0;
	char buf[MAX_MSG] = {}, *s = NULL;

	// Construct a list of user names
	s = buf;
	strncpy(s, "---connected user list---\n", strlen("---connected user list---\n"));
	s += strlen("---connected user list---\n");
	for (i = 0; i < MAX_USER; i++) {
		if (user_list[i].m_status == SLOT_EMPTY)
			continue;
		flag = 1;
		strncpy(s, user_list[i].m_user_id, strlen(user_list[i].m_user_id));
		s = s + strlen(user_list[i].m_user_id);
		strncpy(s, "\n", 1);
		s++;
	}

  // Test whether any users were found
	if (flag == 0) {
		strcpy(buf, "<no users>\n");
	} else {
		s--;
		strncpy(s, "\0", 1);
	}

  // Check if the index passed was out of bounds, otherwise pass the user list
	if(idx < 0) {
    printf("%s\n",buf);
	} else {
		// Write to the given pipe fd
		if (write(user_list[idx].m_fd_to_user, buf, strlen(buf) + 1) < 0)
			perror("writing to server shell");
	}

	return 0;
}

/*
 * Add a new user
 */
int add_user(int idx, USER * user_list, int pid, char * user_id, int pipe_to_child, int pipe_to_parent)
{
  /*
   * Populate the user_list structure with the arguments passed to this function
   * Return the index of user added
   */
  user_list[idx].m_pid = pid;
  strncpy(user_list[idx].m_user_id,user_id, strlen(user_id));
  user_list[idx].m_fd_to_user = pipe_to_child;
  user_list[idx].m_fd_to_server = pipe_to_parent;
  user_list[idx].m_status = SLOT_FULL;
  user_list[idx].m_pid = pid;


	return idx;
}

/*
 * Kill a user
 */
void kill_user(int idx, USER * user_list) {
	/*
   * Kill a user (specified by idx) by using the systemcall kill()
	 * Wait until the process has been terminated
   */
  kill(user_list[idx].m_pid,SIGKILL);
  waitpid(user_list[idx].m_pid,NULL,0);
}

/*
 * Perform cleanup actions after the used has been killed
 */
void cleanup_user(int idx, USER * user_list)
{
	/*
   * m_pid should be set back to -1
	 * m_user_id should be set to zero, using memset()
	 * Close all the fd
   * Set the value of all fd back to -1
   * Set the status back to empty
   */
	user_list[idx].m_pid = -1;
	memset(user_list[idx].m_user_id, '\0', MAX_USER_ID);
	user_list[idx].m_fd_to_user = -1;
	user_list[idx].m_fd_to_server = -1;
	user_list[idx].m_status = SLOT_EMPTY;
}

/*
 * Kills the user and performs cleanup
 */
void kick_user(int idx, USER * user_list) {
	/*
   * Kill_user to end the process
   * Clean up the slot (user_list[idx]) for further use
   */
  kill_user(idx,user_list);
  cleanup_user(idx,user_list);
}

/*
 * broadcast message to all users
 */
int broadcast_msg(USER * user_list, char *buf, char *sender)
{
	/*
   * Iterate over the user_list and if a slot is full, and the user is not the sender itself,
   * then send the message to that user
   * Return zero on success
   */

  int i = 0;
  char buf_tmp[MAX_MSG];
  char *serv = "SERVER";
  // If sender is not the server then add their name to the prompt
  if (strcmp(sender, serv) != 0) {
    strcpy(buf_tmp, "\n");
    strcat(buf_tmp, sender);
    strcat(buf_tmp, ":");
  }
  // Concatenate the original intended message
  strcat(buf_tmp, buf);
  for (int i = 0;i<MAX_USER;i++) {
    // Send message to everyone who isn't the sender
    if (strcmp(user_list[i].m_user_id,sender)!=0 && user_list[i].m_status==SLOT_FULL) {
      // Attempt to write, return error message if failed
      if (write(user_list[i].m_fd_to_user,buf_tmp,sizeof(buf_tmp)) == -1){
	       perror("\nCouldn't write to pipe\n");
      }
    }
  }
	return 0;
}

/*
 * Find user index for given user name
 */
int find_user_index(USER * user_list, char * user_id)
{
	/*
   * Go over the  user list to return the index of the user which matches the argument user_id
	 * Return -1 if not found
   */
	int i, user_idx = -1;

	if (user_id == NULL) {
		fprintf(stderr, "NULL name passed.\n");
		return user_idx;
	}
	for (i=0;i<MAX_USER;i++) {
		if (user_list[i].m_status == SLOT_EMPTY)
			continue;
		if (strcmp(user_list[i].m_user_id, user_id) == 0) {
			return i;
		}
	}

	return -1;
}

/*
 * Given a command's input buffer, extract name
 */
int extract_name(char * buf, char * user_name)
{
	char inbuf[MAX_MSG];
    char * tokens[16];
    strcpy(inbuf, buf);
    int token_cnt = parse_line(inbuf, tokens, " ");
    if(token_cnt >= 2) {
        strcpy(user_name, tokens[1]);
        return 0;
    }

    return -1;
}

int extract_text(char *buf, char * text)
{
    char inbuf[MAX_MSG];
    char * tokens[16];
    char * s = NULL;
    strcpy(inbuf, buf);

    int token_cnt = parse_line(inbuf, tokens, " ");

    if(token_cnt >= 3) {
        //Find " "
        s = strchr(buf, ' ');
        s = strchr(s+1, ' ');

        strcpy(text, s+1);
        return 0;
    }

    return -1;
}

/*
 * Send personal message
 */
void send_p2p_msg(int idx, USER * user_list, char *buf)
{
  /*
   * Get the target user by name using extract_name() function
	 * Find the user id using find_user_index()
	 * If user not found, write back to the original user "User not found", using the write()function on pipes.
	 * If the user is found then write the message that the user wants to send to that user.
   */
  char user_name[MAX_USER_ID];
  int user_index;
  char msg[MAX_MSG];
  char inbuf[MAX_MSG];

  // Test user input
  int j = extract_name(buf,user_name);
  if (j == -1) {
	   perror("Error extracting name");
  }
  int i = extract_text(buf,msg);
  if (i== -1) {
	   perror("Error extracting text");
  }

  // Handles formatting of the message
  strcpy(inbuf, "\n");
  strcat(inbuf, user_list[idx].m_user_id);
  strcat(inbuf, " : ");
  strcat(inbuf,msg);

  user_index = find_user_index(user_list,user_name);
  if (user_index == -1 || user_list[user_index].m_status!=SLOT_FULL) {
    // Error handling for user existence
    if (write(user_list[idx].m_fd_to_user,"User not found",strlen("User not found")) == -1){
	     perror("\nCouldn't write to pipe\n");
     }
  } else {
    // Print msg in server
    printf("\nmsg : %s : %s\n", user_list[idx].m_user_id, msg);
    print_prompt("admin");
    // Attempt to write message to user
    if (write(user_list[user_index].m_fd_to_user,inbuf,sizeof(msg)) == -1){
	     perror("\nCouldn't write to pipe\n");
    }
  }
}

/*
 * Populates the user list initially
 */
void init_user_list(USER * user_list) {
	/*
   * Iterate over the MAX_USER
	 * Memset() all m_user_id to zero
	 * Set all fd to -1
	 * Set the status to be EMPTY
   */
	int i=0;
	for(i=0;i<MAX_USER;i++) {
		user_list[i].m_pid = -1;
		memset(user_list[i].m_user_id, '\0', MAX_USER_ID);
		user_list[i].m_fd_to_user = -1;
		user_list[i].m_fd_to_server = -1;
		user_list[i].m_status = SLOT_EMPTY;
	}
}


/* ---------------------End of the functions that implementServer functionality -----------------*/


/* ---------------------Start of the Main function ----------------------------------------------*/
int main(int argc, char * argv[])
{

	int nbytes = 0;
	setup_connection("500"); // Specifies the connection point as argument.

	USER user_list[MAX_USER];
	init_user_list(user_list);   // Initialize user list

	char buf[MAX_MSG];
	fcntl(0, F_SETFL, fcntl(0, F_GETFL)| O_NONBLOCK);
	print_prompt("admin");
	int idx_tmp;
  int idx_pipe;
  int usr_count;
  pid_t pid = 5;
  // Signal handler for server
  void handle_interrupt(int sig) {
    printf("%s\n","Server interrupt");
    for (int s = 0; s<MAX_USER; s++) {
      if (user_list[s].m_status == SLOT_FULL) {
        kick_user(s, user_list);
      }
    }
    exit(0);
  }
  signal(SIGINT,handle_interrupt);

	while(1) {
		/* ------------------------YOUR CODE FOR MAIN--------------------------------*/
    int pipe_SERVER_reading_from_child[2];
    int pipe_SERVER_writing_to_child[2];
    char user_id[MAX_USER_ID];

    int pipe_child_writing_to_user[2];
    int pipe_child_reading_from_user[2];
    if (get_connection(user_id,pipe_child_writing_to_user,pipe_child_reading_from_user)==0) { // if a user connects then create
      pipe(pipe_SERVER_writing_to_child);
      pipe(pipe_SERVER_reading_from_child);

      fcntl(pipe_SERVER_reading_from_child[0], F_SETFL, fcntl(pipe_SERVER_reading_from_child[0], F_GETFL)| O_NONBLOCK); // make read ends of all pipes non blocking
      fcntl(pipe_SERVER_writing_to_child[0], F_SETFL, fcntl(pipe_SERVER_writing_to_child[0], F_GETFL)| O_NONBLOCK);
      fcntl(pipe_child_writing_to_user[0], F_SETFL, fcntl(pipe_child_writing_to_user[0], F_GETFL)| O_NONBLOCK);
      fcntl(pipe_child_reading_from_user[0], F_SETFL, fcntl(pipe_child_reading_from_user[0], F_GETFL)| O_NONBLOCK);
      pid = fork();

      if (pid!=0) {
        // Pipe the pipes connecting server and child if there is a connection
        if (close(pipe_SERVER_writing_to_child[0]) == -1) { // Error handle while closing reading end of writing pipes
          perror("\n Couldn't close file");
	      }
        if (close(pipe_SERVER_reading_from_child[1]) == -1) { // Error handle while closing writing end of reading pipes
          perror("\n Couldn't close file");
	      }
        idx_tmp = find_empty_slot(user_list);
        printf("\nA new user: %s connected. slot:%d\n",user_id, idx_tmp);
        add_user(idx_tmp, user_list, pid-1,user_id,pipe_SERVER_writing_to_child[1], pipe_SERVER_reading_from_child[0]);
        usr_count++;
        print_prompt("admin");
      }
      else {
        // Child needs to close off its ends of the pipes while error handling
        if (close(pipe_child_writing_to_user[0]) == -1) {
          perror("\n Couldn't close file");
        }
        if (close(pipe_child_reading_from_user[1]) == -1) {
          perror("\n Couldn't close file");
        }
        if (close(pipe_SERVER_writing_to_child[1]) == -1) {
          perror("\n Couldn't close file");
        }
        if (close(pipe_SERVER_reading_from_child[0]) == -1) {
          perror("\n Couldn't close file");
        }
      }
    }

		// Handling a new connection using get_connection
    if (pid!=0) {
      char buf2[MAX_MSG];
      // Poll std in
      int nbytesfromstin = read(0,buf,sizeof(buf));
      usleep(50);
      strtok(buf, "\n");
      char user_name[MAX_USER_ID];
      // Predefined buffer in case of admin message
      char admin_buf[MAX_MSG] = "\nadmin-notice: ";
      int user_index = 0;
      if (nbytesfromstin > 0) { // READ FROM STANDARD IN
        switch (get_command_type(buf)) {
          case 0: // List all users
            if (list_users(-1,user_list) == -1){
              perror("Error with listing users");
            }
            break;
          case 1: // Kick: Calls kick_user with the user_index and user_list
            if (extract_name(buf,user_name) == -1){
              perror("Error extracting name");
            }
            user_index = find_user_index(user_list,user_name); // grab username out of buf
      	    if (user_index == -1){
              printf("Cannot find user: %s \n", user_name);
      	    } else {
      	    	kick_user(user_index,user_list); // tokens[2] is the msg to send
              usr_count--;
      	    }
            break;
          case 4: // Exit: Call kick_user on all users before exiting server process
            for (int s = 0; s<MAX_USER; s++) {
              if (user_list[s].m_status == SLOT_FULL) {
                kick_user(s, user_list);
              }
            }
            exit(0);
            break;
          case 5: // Broadcast msg: Sends message to all users
            strcat(admin_buf, buf);
            broadcast_msg(user_list,admin_buf,"SERVER");
            break;
          default:
            break;
        }
        print_prompt("admin");
        memset(buf,'\0',MAX_MSG);
      } else if(nbytesfromstin == 0) {
        perror("Pipe broken.");
      }

      int nbytes = 0;
      for (int i = 0;i<MAX_USER;i++) {
        // Read input from all active pipes in the user_list
        if (user_list[i].m_status == SLOT_FULL) {
          nbytes = read(user_list[i].m_fd_to_server,buf2,sizeof(buf2));
          usleep(50);
          if (nbytes > 0) {
            switch (get_command_type(buf2)) {
              case 0: // List
                if(list_users(i,user_list) == -1) {
                  perror("Unable to list users");
                }
                break;
              case 4: // Exit
                printf("\nThe user: %s seems to be terminated\n", user_list[i].m_user_id);
                kick_user(i,user_list);
                usr_count--;
		            print_prompt("admin");
                break;
              case 2: // P2P
                send_p2p_msg(i,user_list,buf2); // tokens[2] is the msg to send
                break;
              case 5: // Broadcast Message (any other text)
                broadcast_msg(user_list,buf2,user_list[i].m_user_id);
                break;
              default:
                break;
            }
            memset(buf2,'\0',MAX_MSG);
          } else if(nbytes == 0){
            perror("Pipe broken.");
          }
        }
      }
    } else {
      // Child polls its fd from user and server and sends info if necessary
      char msg_from_server[MAX_MSG];
      char msg_from_user[MAX_MSG];
      int nbytes_from_server = 0;
      int nbytes_from_user = 0;
      fcntl(pipe_SERVER_writing_to_child[0], F_SETFL, fcntl(pipe_SERVER_writing_to_child[0], F_GETFL)| O_NONBLOCK);
      fcntl(pipe_child_writing_to_user[0], F_SETFL, fcntl(pipe_child_writing_to_user[0], F_GETFL)| O_NONBLOCK);
      while (1) {

        nbytes_from_server = read(pipe_SERVER_writing_to_child[0],msg_from_server,sizeof(msg_from_server));

        nbytes_from_user = read(pipe_child_reading_from_user[0],msg_from_user,sizeof(msg_from_user));

        if (nbytes_from_server > 0) {
          // Received a message from the server so now we need to write it to the user
          if (write(pipe_child_writing_to_user[1],msg_from_server,sizeof(msg_from_server)) == -1){
            perror("\nCouldn't write to pipe\n");
          }
          memset(msg_from_server,'\0',MAX_MSG);
        }
        if (nbytes_from_user > 0) {
          /*
           * Received a message from a user so now we have to write it to the server
           */
          if (write(pipe_SERVER_reading_from_child[1],msg_from_user,sizeof(msg_from_user)) == -1){
            perror("\nCouldn't write to pipe\n");
          }
          memset(msg_from_user,'\0',MAX_MSG);
        }
        usleep(300);
      }
    }
		/* ------------------------YOUR CODE FOR MAIN--------------------------------*/
    usleep(500);
	}
}

/* --------------------End of the main function ----------------------------------------*/
