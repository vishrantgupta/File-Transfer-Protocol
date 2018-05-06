/********************************************************************

 util5srv.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=2

 *********************************************************************/

#include	"prog5srv.h"
#include	"wrap5srv.h"

// commands
const char *cmds[] = { "", "?", "bye", "cd", "cdup", "close", "disconnect",
		"help", "lcd", "open", "pwd", "quit" };

// for handling ~ tilda
wordexp_t exp_result;

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
 *          util5srv.c
 *
 */
void trim(char* str) {

	// size of str
	size_t ln = strlen(str) - 1;

	// replace last with \0
	if (*str && str[ln] == BACKSLASH_N)
		str[ln] = BACKSLASH_ZERO;
}

void str_echo(int conn_fd) {

	// readline size
	int size;

	// command
	char cmd[MAXLINE];

	// argument 1
	char arg1[MAXLINE];

	// argument 2
	char arg2[MAXLINE];

	// send data
	char sendline[MAXLINE];

	// buffer data
	char buffer[MAXLINE];

	// result
	char *result;

	// command id
	cmd_id id;

	while ((size = Readline(conn_fd, buffer, MAXLINE)) > 0) {

		// setting all to 0
		buffer[strlen(buffer) - 1] = 0;

		// getting command id
		id = get_args(buffer, cmd, arg1, arg2);

		switch (id) {

		case PWD_: // pwd command

			// get current working directory
			result = Getcwd(0, 0);

			// putting data into sendline
			snprintf(sendline, sizeof(sendline), PWD_OUTPUT, errno, result);
			break;

		case CD_: // cd command

			new_dir(arg1);

			if (errno == 0) {
				// putting data into sendline
				snprintf(sendline, sizeof(sendline), CD_OUTPUT, errno);
			} else {
				// error occured, writing only error number
				snprintf(sendline, sizeof(sendline), ERROR_OUTPUT, errno);
			}
			break;

		case CDUP_: // cdup command

			// changing to parent directory
			Chdir(CDUP_COMMAND);

			// no error, putting to sendline
			if (errno == 0) {
				snprintf(sendline, sizeof(sendline), CD_OUTPUT, errno);
			} else {
				// error occured, writing only error number
				snprintf(sendline, sizeof(sendline), ERROR_OUTPUT, errno);
			}
			break;
		default: // empty command sent
			break;
		}

		// writing data to client
		Writen(conn_fd, sendline, strlen(sendline));

	}
}

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
 *          util5srv.c
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
 * Name: get_args
 *
 * Prototype:
 *          cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2)
 *
 * Description:
 *          get args
 *
 * Header files:
 *          util5srv.c
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
 *          bool new_dir(char *dir)
 *
 * Description:
 *          handles cd command
 *
 * Header files:
 *          util5srv.c
 *
 */
bool new_dir(char *dir) {

	// if no directory provided
	if (strcmp(dir, BLANK) == ZERO) {

		// getting current working directory
		fprintf(stdout, "%s", Getcwd(0, 0));
		return true;
	}

	// expanded path
	char path[MAXLINE];

	if (strcmp(dir, USER_HOME) == 0) {
		// expand path
		wordexp(path, &exp_result, 0);
	} else {
		// path provided by user
		strcpy(path, dir);
	}

	// change directory to resolved path
	Chdir(path);

	// if any error occurred in changing path
	return errno == 0 ? true : false;
}
