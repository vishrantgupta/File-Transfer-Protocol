/********************************************************************

 prog5ftp.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=1

 *********************************************************************/

#include "util5cli.h"
#include "prog5cli.h"
#include "wrap5cli.h"

// usage of commands
char* usage[] =
		{
				"The client host and an optional port number with which ftp is to communicate may be specified on the command line. If this is done, ftp will immediately attempt to establish a connection to an FTP server on that host; otherwise, ftp will enter its command interpreter and await instructions from the user.  When ftp is awaiting commands from the user the prompt 'ftp>' is provided to the user.  The following commands are recognized by ftp:",
				"A synonym for help.",
				"Terminate the FTP session with the remote server and exit FTP. An EOF will also terminate the session and exit.",
				"Change the working directory on the remote machine to remote-directory",
				"Change the remote machine working directory to the parent of the current remote machine working directory",
				"Terminate the FTP session with the remote server, and return to the command interpreter.",
				"A synonym for close",
				"Print an informative message about the meaning of command. If no argument is given, FTP prints a list of the known commands.",
				"Change the working directory on the local machine. If no directory is specified, the user’s home directory is used.",
				"Establish a connection to the specified host FTP server. An optional port number may be supplied, in which case, FTP will attempt to contact an FTP server at that port.",
				"Print the name of the current working directory on the remote machine.",
				"A synonym for bye." };

// command list
const char* cmds[] = { "", "?", "bye", "cd", "cdup", "close", "disconnect",
		"help", "lcd", "open", "pwd", "quit" };

// for handling ~ tilda
wordexp_t exp_result;

/*
 * Name: find_id
 *
 * Prototype:
 *          cmd_id find_id(char* cmd)
 *
 * Description:
 *          get command id
 *
 * Header files:
 *          util5cli.c
 *
 */
cmd_id find_id(char* cmd) {

	// local copy of cd
	char* l_cmd = cmd;

	// if cd is null return -1
	if (l_cmd == NULL) {
		return NEG_;
	}

	// size of cmd
	int size = sizeof(cmds) / sizeof(cmds[0]);

	// compare and return index
	for (int i = 0; i < size; ++i) {
		trim(l_cmd);

		int cmp = strcmp(l_cmd, cmds[i]);

		// return index
		if (cmp == 0) {
			return i;
		}
	}

	// not found return -1
	return NEG_;
}

/*
 * Name: trim
 *
 * Prototype:
 *          void trim(char* str)
 *
 * Description:
 *          trim string
 *
 * Header files:
 *          util5cli.c
 *
 */
void trim(char* str) {

	// size of str
	size_t ln = strlen(str) - 1;

	// replace last with \0
	if (*str && str[ln] == BACKSLASH_N)
		str[ln] = BACKSLASH_ZERO;
}

/*
 * Name: prnt_cmd_list
 *
 * Prototype:
 *          void prnt_cmd_list()
 *
 * Description:
 *          print all list of help
 *
 * Header files:
 *          util5cli.c
 *
 */
void prnt_cmd_list() {
	int size = (sizeof(usage) / sizeof(usage[0]));

	// iterate and print all commands
	for (int var = 0; var < size; ++var) {

		// command and usage index is same
		printf("%s\n", cmds[var]);
		printf("\t%s\n\n", usage[var]);
	}
}

/*
 * Name: prnt_cmd_help
 *
 * Prototype:
 *          void prnt_cmd_help()
 *
 * Description:
 *          print perticular cmd help
 *
 * Header files:
 *          util5cli.c
 *
 */
void prnt_cmd_help(char* cmd) {

	// get index
	cmd_id cid = find_id(cmd);

	// print invlaid command
	if (cid == NEG_) {
		printf(HELP_INVALID, cmd);
		return;
	}

	// print usage
	printf(HELP_CMD, cmd, usage[cid]);
}

/*
 * Name: get_args
 *
 * Prototype:
 *          cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2)
 *
 * Description:
 *          get args
 *
 * Header files:
 *          util5cli.c
 *
 */
cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2) {

	// to tokenize
	char* temp = strtok(buf, SPACE);

	int count = 0;
	while (temp != NULL) {

		// remove extra chars
		trim(temp);

		// command
		if (count == CMD) {
			strcpy(cmd, temp);
		}

		// argument 1
		if (count == ARG1) {
			strcpy(arg1, temp);
		}

		// argument 2
		if (count == ARG2) {
			strcpy(arg2, temp);
		}

		temp = strtok(NULL, SPACE);

		count++;
	}

	// get index
	cmd_id cid = find_id(cmd);

	// return index
	return cid;
}

/*
 * Name: new_dir
 *
 * Prototype:
 *          bool new_dir(char* dir, cmd_id id, int socket_fd)
 *
 * Description:
 *          handle cd , lcd cdup command
 *
 * Header files:
 *          util5cli.c
 *
 */
bool new_dir(char* dir, cmd_id id, int socket_fd) {

	// lcd command
	if (id == LCD_) {

		// take home directory ~
		if (dir[0] == BACKSLASH_ZERO) {
			dir = USER_HOME;
		}

		// trim
		trim(dir);

		// expand path
		wordexp(dir, &exp_result, 0);

		// change dir
		Chdir(exp_result.we_wordv[0]);

	} else if (id == CD_) { // cd command

		// cd input
		char cd_input[MAXLINE];

		// directory name
		char cd_dir[MAXLINE];

		// directory not provided
		if (dir[0] == BACKSLASH_ZERO) {
			printf(CD_MSG);

			// taking ip address
			Fgets(cd_input, MAXLINE, stdin);

			// parsing command
			get_args(cd_input, cd_dir, NULL, NULL);
		} else {
			strcpy(cd_dir, dir);
		}

		// removing not required char
		trim(cd_dir);

		// if again ip address not provided
		if (cd_dir[0] == BACKSLASH_ZERO || cd_dir[0] == BACKSLASH_N) {
			printf(CD_USAGE);

			return false;
		}

		// size of array
		int size = sizeof(cmds[CD_]) + sizeof(cd_dir) + 1;

		// server command
		char* s_command = (char*) malloc(size);

		// appending server command
		strcpy(s_command, cmds[CD_]);
		strcat(s_command, SPACE);
		strcat(s_command, cd_dir);

		// sending to server
		str_echo(socket_fd, s_command);

	} else if (id == CDUP_) { // cdup command

		// appendng command
		char cmd[MAXLINE];
		strcpy(cmd, cmds[CDUP_]);

		// sending to server
		str_echo(socket_fd, cmd);
	}

	return true;
}

/*
 * Name: not_connected
 *
 * Prototype:
 *          void not_connected()
 *
 * Description:
 *          for printing not connected message
 *
 * Header files:
 *          util5cli.c
 *
 */
void not_connected() {
	printf(NOT_CONNECTED);
}
