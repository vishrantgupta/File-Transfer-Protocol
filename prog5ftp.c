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

#include "prog5cli.h"
#include "util5cli.h"
#include "wrap5cli.h"

/*
 * Name: main
 *
 * Description:
 *          FTP Client
 *
 */
int main(int argc, char** argv) {

	// buffer to hold user input
	char buffer[MAXLINE];

	// ip address
	char ip_address[MAXLINE];

	// socket fd
	int socket_fd = -1;

	// command id
	cmd_id id;

	// tokenized command
	char command[MAXLINE];

	// argument 1
	char arg1[MAXLINE];

	// argument 2
	char arg2[MAXLINE];

	// command line input, if ip address and port is provided while executing it will
	// directly try to connect to server
	if (argc > 3) {
		fprintf(stderr,
				"Invalid number of parameters: Usage: %s [IP address]\n",
				argv[0]);

		exit(1);
	}

	// only ip address provided
	if (argc == 2) {
		// copying ip address
		strcpy(arg1, argv[1]);

		id = OPEN_;

		// goto open
		goto s_cmd;
	}

	// ip address and port provided
	if (argc == 3) {
		// copying ip address and port
		strcpy(arg1, argv[1]);
		strcpy(arg2, argv[2]);

		id = OPEN_;

		// goto open
		goto s_cmd;
	}

	// quit flag
	bool quit = false;

	// prompt flag
	bool prompt = true;

	// printing prompt
	printf(PROMPT);

	while (!quit) {

		// initializing command
		memset(command, 0, MAXLINE);

		// initializing arg1
		memset(arg1, 0, MAXLINE);

		// initializing arg2
		memset(arg2, 0, MAXLINE);

		prompt = true;

		// taking input for FTP
		Fgets(buffer, MAXLINE, stdin);

		// command id
		id = get_args(buffer, command, arg1, arg2);

		// goto statement
		s_cmd:

		switch (id) {

		case NEG_: // invalid command

			fprintf(stderr, INVALID_CMD);
			break;

		case QUIT_: // quit and bye command
		case BYE_:
			quit = true;
			prompt = false;
			break;

		case HELP_: // help and ? command
		case QM_:

			// printing whole help
			if (arg1[0] == BACKSLASH_ZERO) {
				prnt_cmd_list();
			} else {
				// printing specific command
				prnt_cmd_help(arg1);
			}

			break;

		case LCD_: // lcd command
			new_dir(arg1, id, socket_fd);
			break;

		case CD_: // cd command
			not_connected();
			break;

		case OPEN_: // open command

			// ip address and port not provided
			if (arg1[0] == 0) {
				printf(TO_MSG);

				// taking ip address
				Fgets(buffer, MAXLINE, stdin);

				// parsing command
				get_args(buffer, ip_address, arg2, NULL);
			} else {
				// ip address provided
				strcpy(ip_address, arg1);
			}

			// if again ip address not provided
			if (ip_address[0] == BACKSLASH_ZERO || ip_address[0] == BACKSLASH_N) {
				printf(OPEN_MSG);
				break;
			}

			// sending control to client
			if (client(ip_address, arg2, true)) {
				exit(0);
			} else {
				// setting prompt based on return value of client
				prompt = true;
			}

			break;

		case CLOSE_: // close and disconnect command in ftp
		case DISCONNECT_:

			// not connected in ftp
			not_connected();
			break;

		case PWD_: // pwd command

			// not connected in ftp
			not_connected();
			break;

		case CDUP_: // cdup command

			// not connected in ftp
			not_connected();
			break;

		case ZERO_: // just enter is pressed again printing prompt
		default:
			break;
		}

		// printing prompt based on prompt flag
		if (prompt) {
			printf(PROMPT);
		}

	}

}
