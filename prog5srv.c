/********************************************************************

 prog5srv.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=2

 *********************************************************************/

#include"prog5srv.h"
#include"wrap5srv.h"

// exit flags
extern bool exit_flags[];

/*
 * Name: init_flags
 *
 * Prototype:
 *          void init_flags()
 *
 * Description:
 *          Initialize flags
 *
 * Header files:
 *          prog5cli.c
 *
 */
void init_flags() {

	// setting not exit for all except listen, socket, bind
	for (int i = 0; i < NO_OF_FUNCTIONS + 1; i++) {
		exit_flags[i] = false;
	}

	// exit for listen, socket and bind
	exit_flags[LISTEN] = true;
	exit_flags[SOCKET] = true;
	exit_flags[BIND] = true;

}

/*
 * Name: main
 *
 * Description:
 *          FTP Server
 *
 * Header files:
 *          prog5cli.c
 *
 */
int main(int argc, char *argv[]) {

	// if parameters is greater than 2 then its an invalid command
	if (argc > 2) {
		fprintf(stderr,
				"Invalid number of parameters: Usage: %s [portNumber]\n",
				argv[0]);

		exit(1);
	}

	// port number of server
	int port_no = -1;

	// listen file descriptor
	int listen_fd = -1;

	// connection file descriptor
	int conn_fd = -1;

	// child PID
	pid_t child_pid = -1;

	// server details
	struct sockaddr_in server_addr;

	// initializing flags
	init_flags();

	// creating socket
	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

	// clearing socket addr
	bzero(&server_addr, sizeof(server_addr));

	// IPv4
	server_addr.sin_family = AF_INET;

	// accepting connection from any ip
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// taking default port number when port number is not passed
	if (argc == 2) {
		port_no = atoi(argv[1]);
	} else {
		port_no = DEFAULT_PORT;
	}

	// converting to kernel understandable form
	server_addr.sin_port = htons(port_no);

	// bind to specified port number
	Bind(listen_fd, (SA*) &server_addr, sizeof(server_addr));

	// listen for listen fd
	Listen(listen_fd, LISTENQ);

	// signal handler
	Signal(SIGCHLD, signal_handler);

	while (true) {

		// accept connection
		conn_fd = Accept(listen_fd, NULL, NULL);
		if ((child_pid = Fork()) == 0) {

			// close parent copy
			Close(listen_fd);

			// write response
			str_echo(conn_fd);

			// close connection
			Close(conn_fd);
			exit(0);
		}

		Close(conn_fd);
	}

	// close connection
	Close(listen_fd);
	exit(0);
}

/*
 * Name: signal_handler
 *
 * Prototype:
 *          void signal_handler(int signo)
 *
 * Description:
 *          handles the signal from kernel
 *
 */
void signal_handler(int signal_number) {

	int wstatus;

	Signal(SIGCHLD, signal_handler);

	Wait(&wstatus);

}
