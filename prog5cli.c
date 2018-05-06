/********************************************************************

 prog5cli.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=1

 *********************************************************************/

#include "prog5cli.h"
#include "wrap5cli.h"
#include "util5cli.h"

/*
 * Name: close_connection
 *
 * Prototype:
 *          void close_connection(int socket_fd)
 *
 * Description:
 *          Close connection
 *
 * Header files:
 *          prog5cli.c
 *
 */
void close_connection(int socket_fd);

/*
 * Name: client
 *
 * Prototype:
 *          bool client(char* ip_addr, char* server_port, bool prompt)
 *
 * Description:
 *          Executes command on client and server
 *
 * Header files:
 *          prog5cli.c
 *
 */
bool client(char* ip_addr, char* server_port, bool prompt) {

	// removing backslash
	trim(ip_addr);
	trim(server_port);

	// socket fd
	int socket_fd = -1;

	// port number
	int port_no = -1;

	// connection return value
	int conn = 0;

	// inet pton return value
	int inet_msg = 0;

	// sock addr struct
	struct sockaddr_in servaddr;

	// resetting values
	bzero(&servaddr, sizeof(servaddr));

	// ip v4 family type
	servaddr.sin_family = AF_INET;

	// taking default port if no port is provided
	if (server_port[0] == BACKSLASH_ZERO || server_port[0] == BACKSLASH_N) {
		port_no = DEFAULT_PORT;
	} else {
		// if port is provided
		port_no = atoi(server_port);

	}

	// converting to network byte order
	servaddr.sin_port = htons(port_no);

	// converting to machine understandable format
	inet_msg = Inet_pton(AF_INET, ip_addr, &servaddr.sin_addr);

	// if in correct address and return control to FTP
	if (inet_msg < 0) {
		return false;
	}

	// creating socket
	socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

	// if socket not created return control to FTP
	if (socket_fd < 0) {
		return false;
	}

	// creating connection
	conn = Connect(socket_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	// if connection failed return control to FTP
	if (conn < 0) {
		return false;
	}

	// print connection successful message
	printf(CONNECTED_MSG, ip_addr);

	return str_cli(socket_fd, ip_addr, prompt);
}

/*
 * Name: str_cli
 *
 * Prototype:
 *          bool str_cli(int sockfd, char* saddr, bool prompt)
 *
 * Description:
 *          Executes command on client and server
 *
 * Header files:
 *          prog5cli.c
 *
 */
bool str_cli(int sockfd, char* saddr, bool prompt) {

	// user input
	char buffer[MAXLINE];

	// command
	char command[MAXLINE];

	// argument 1
	char arg1[MAXLINE];

	// argument 2
	char arg2[MAXLINE];

	// command id
	cmd_id id;

	// quit flag
	bool quit = false;

	// return value to FTP
	bool return_val = true;

	// printing prompt
	printf(PROMPT);

	while (!quit) {

		// resetting quit
		quit = false;

		// initializing variables
		memset(command, 0, MAXLINE);
		memset(arg1, 0, MAXLINE);
		memset(arg2, 0, MAXLINE);

		// taking user nput
		Fgets(buffer, MAXLINE, stdin);

		// parsing user input
		id = get_args(buffer, command, arg1, arg2);

		// switch
		switch (id) {
		case NEG_: // invalid command

			fprintf(stderr, INVALID_CMD);
			break;

		case QUIT_: // quit and bye command
		case BYE_:

			// closing connection
			close_connection(sockfd);

			// no prompt
			prompt = false;

			// quit true
			quit = true;

			// quitting ftp from FTP main
			return_val = true;
			break;

		case HELP_: // help and ? command
		case QM_:

			// print whole list
			if (arg1[0] == BACKSLASH_ZERO) {
				prnt_cmd_list();
			} else {
				// print for perticular command
				prnt_cmd_help(arg1);
			}

			break;

		case LCD_: // lcd, cd and cdup command
		case CD_:
		case CDUP_:

			// calling new dir for handling these command
			new_dir(arg1, id, sockfd);
			break;

		case OPEN_: // open command, already connected
			printf(ALREADY_CONNECTED, saddr);
			break;

		case CLOSE_: // close and disconnect command
		case DISCONNECT_:
			close_connection(sockfd);

			// no prompt
			prompt = false;

			// return value false to exit
			return_val = false;

			// quit from whle loop
			quit = true;
			break;

		case PWD_: // pwd command

			// send to server
			str_echo(sockfd, buffer);
			break;

		case ZERO_: // enter key pressed
		default:
			break;
		}

		// print prompt based on prompt flag
		if (prompt) {
			printf(PROMPT);
		}

	}

	return return_val;
}

/*
 * Name: close_connection
 *
 * Prototype:
 *          void close_connection(int socket_fd)
 *
 * Description:
 *          close connection
 *
 * Header files:
 *          prog5cli.c
 *
 */
void close_connection(int socket_fd) {
	Close(socket_fd);
	printf(GOODBYE);
}

/*
 * Name: str_echo
 *
 * Prototype:
 *          void str_echo(int sockfd, char* command)
 *
 * Description:
 *          send to server
 *
 * Header files:
 *          prog5cli.c
 */
void str_echo(int sockfd, char* command) {

	// received data
	char received_data[MAXLINE];

	// writing to server
	Writen(sockfd, command, strlen(command));
	Writen(sockfd, NEWLINE, strlen(NEWLINE));

	// reading from server
	Readline(sockfd, received_data, MAXLINE);

	// if value at index 0 is 0 then its error
	// then print strerror
	if (received_data[0] != ZERO) {
		fprintf(stderr, "%s\n", strerror(atoi(received_data)));
	} else {
		// command executed successfully in server, ignoring success code
		printf("%s", (received_data + IGNORE_SUCCUESS_CODE));
	}

}
