/********************************************************************

 wrap5srv.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=2

 *********************************************************************/

#include "wrap5srv.h"

// exit flags, setting all to false
bool exit_flags[NO_OF_FUNCTIONS] = { false };

/*
 * Name: Chdir
 *
 * Prototype:
 *          int Chdir(const char *path)
 *
 * Description:
 *          change directory
 *
 * Header files:
 *          wrap5srv.c
 *
 */
int Chdir(const char *path) {

	errno = 0; // resetting error number

	int msg = chdir(path);
	if (msg < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[CHDIR]) {
			exit(CHDIR);
		}
	}

	return msg;
}

/*
 * Name: Getcwd
 *
 * Prototype:
 *          char *Getcwd(char *buf, size_t size)
 *
 * Description:
 *          Get current working directory
 *
 * Header files:
 *          wrap5srv.c
 *
 */
char* Getcwd(char *buf, size_t size) {
	errno = 0; // resetting error number

	char *msg = getcwd(buf, size);
	if (msg == NULL) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[GETCWD]) {
			exit(GETCWD);
		}
	}

	return msg;
}

/*
 * Name: Signal
 *
 * Prototype:
 *          Sigfunc *Signal(int signo, Sigfunc *func)
 *
 * Description:
 *          Signal
 *
 * Header files:
 *          wrap5srv.c
 *
 */
Sigfunc *Signal(int signal_number, Sigfunc *signal_handler_func) {
	struct sigaction action, oact;

	action.sa_handler = signal_handler_func;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (signal_number == SIGALRM) {
		// SunOS 4.x
#ifdef SA_INTERRUPT
		action.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		// SVR4, 4.4BSD
#ifdef SA_RESTART
		action.sa_flags |= SA_RESTART;
#endif
	}

	if (sigaction(signal_number, &action, &oact) < 0) {
		return (SIG_ERR);
	}

	return (oact.sa_handler);
}

/*
 * Name: Readline
 *
 * Prototype:
 *          ssize_t Readline(int, void*, size_t)
 *
 * Description:
 *          Read data from socket
 *
 * Header files:
 *          wrap5srv.c
 *
 */
ssize_t Readline(int socket_fd, void* str, size_t length) {

	errno = 0; // resetting error number

	ssize_t line = readline(socket_fd, str, length);

	if (line < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[READLINE]) {
			exit(READLINE);
		}
	}

	return line;
}

/*
 * Name: Wait
 *
 * Prototype:
 *          pid_t Wait(int *wstatus)
 *
 * Description:
 *          Wait for the process
 *
 * Header files:
 *          wrap5srv.c
 *
 */
pid_t Wait(int *wstatus) {

	errno = 0; // resetting error number

	pid_t pid = wait(wstatus);

	if (pid < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[WAIT]) {
			exit(WAIT);
		}
	}

	if (WIFEXITED(*wstatus)) {
		fprintf(stdin, WAIT_ERROR, pid, WEXITSTATUS(*wstatus));
	}

	return pid;
}

/*
 * Name: Fork
 *
 * Prototype:
 *          int Fork()
 *
 * Description:
 *          Fork the process
 *
 * Header files:
 *          wrap5srv.c
 *
 */
pid_t Fork() {

	errno = 0; // resetting error number

	int fork_val = fork();

	if (fork_val < 0) {
		fprintf(stderr, FORK_ERROR, fork_val);

		// conditional exit
		if (exit_flags[FORK]) {
			exit(FORK);
		}
	}

	return fork_val;
}

/*
 * Name: Fgets
 *
 * Prototype:
 *          char *Fgets(char *s, int size, FILE *stream)
 *
 * Description:
 *          Read data from stream
 *
 * Header files:
 *          wrap5srv.h
 *
 */
char *Fgets(char *s, int size, FILE *stream) {

	errno = 0; // resetting error number

	char* line = fgets(s, size, stream);

	if (line == NULL && errno != 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[FGETS]) {
			exit(FGETS);
		}
	}

	return line;
}

/*
 * Name: Socket
 *
 * Prototype:
 *          int Socket(int family, int type, int protocol)
 *
 * Description:
 *          Implementation for Socket wrapper
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Socket(int family, int type, int protocol) {

	errno = 0; // resetting error number

	int socket_fd = socket(family, type, protocol);

	if (socket_fd < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[SOCKET]) {
			exit(SOCKET);
		}

	}

	return socket_fd;
}

/*
 * Name: Bind
 *
 * Prototype:
 *          int Bind(int socket_fd, const struct sockaddr *address, socklen_t addr_len)
 *
 * Description:
 *          Implementation for Bind wrapper
 *
 * Header files:
 *          wrap5srv.c
 *
 */
int Bind(int socket_fd, const struct sockaddr *address, socklen_t addr_len) {

	errno = 0; // resetting error number

	int return_val = bind(socket_fd, address, addr_len);

	if (return_val < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[BIND]) {
			exit(BIND);
		}

	}

	return return_val;
}

/*
 * Name: Listen
 *
 * Prototype:
 *          int Listen(int socket_fd, int backlog)
 *
 * Description:
 *          Implementation for listen wrapper
 *
 * Header files:
 *          wrap5srv.c
 *
 */
int Listen(int socket_fd, int backlog) {

	errno = 0; // resetting error number

	int listen_id = listen(socket_fd, backlog);

	// conditional exit
	if (listen_id < 0) {
		perror(ERROR);

		if (exit_flags[LISTEN]) {
			exit(LISTEN);
		}
	}

	return listen_id;
}

/*
 * Name: Close
 *
 * Prototype:
 *          int Close(int file_desc)
 *
 * Description:
 *          Implementation for Close wrapper
 *
 * Header files:
 *          wrap5srv.c
 *
 */
int Close(int file_desc) {

	errno = 0; // resetting error number

	int close_val = close(file_desc);

	if (close_val < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[CLOSE]) {
			exit(CLOSE);
		}
	}

	return close_val;
}

/*
 * Name: Accept
 *
 * Prototype:
 *          int Accept(int socket_fd, struct sockaddr *address, socklen_t *addr_len)
 *
 * Description:
 *          Implementation for accept wrapper
 *
 * Header files:
 *          wrap5srv.c
 *
 */
int Accept(int socket_fd, struct sockaddr *address, socklen_t *addr_len) {

	errno = 0; // resetting error number

	int return_val = accept(socket_fd, address, addr_len);

	if (return_val < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[ACCEPT]) {
			exit(ACCEPT);
		}
	}

	return return_val;
}

/*
 * Name: Writen
 *
 * Prototype:
 *          ssize_t Writen(int, void*, size_t)
 *
 * Description:
 *          write data to socket
 *
 * Header files:
 *          wrap5srv.c
 *
 */
ssize_t Writen(int socket_fd, const void* str, size_t length) {

	errno = 0; // resetting error number

	ssize_t line = writen(socket_fd, str, length);

	if (line < 0) {
		perror(ERROR);

		// conditional exit
		if (exit_flags[WRITEN]) {
			exit(WRITEN);
		}
	}

	return line;
}
