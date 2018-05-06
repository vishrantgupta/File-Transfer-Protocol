/********************************************************************

 wrap3cli.c

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 3
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  03/10/17

 Purpose:   Header file to get author information
 from server

 Execution: Make execute N=3 T=2

 *********************************************************************/

#include    "wrap5cli.h"
#include 	"prog5cli.h"

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
 *          wrap1cli.h
 *
 */
int Socket(int family, int type, int protocol) {

	errno = 0;

	int socket_fd = socket(family, type, protocol);

	if (socket_fd < 0) {
		perror(ERROR);

//        if (exit_flags[SOCKET] == TRUE) {
//            exit(-1);
//        }

	}

	return socket_fd;
}

/*
 * Name: Inet_pton
 *
 * Prototype:
 *          int Inet_pton(int family, const char *strptr, void *addrptr)
 *
 * Description:
 *          Implementation for Inet_pton wrapper
 *
 * Header files:
 *          wrap1cli.h
 *
 */
int Inet_pton(int family, const char *strptr, void *addrptr) {

	errno = 0;

	int addr = inet_pton(family, strptr, addrptr);

	if (addr < 0) {
		perror(ERROR);

//        if (exit_flags[INET_PTON] == TRUE) {
//            exit(-2);
//        }

	} else if (addr == 0) {
		addr = -1;

		char msg[MAXLINE];
		strcpy(msg, strptr);

		trim(msg);
		printf(INET_PTON_MSG, msg);

//        fprintf(stderr,
//                "Source does not contain a character string representing a "
//                        "valid network address in the specified address family\n");

//        if (exit_flags[INET_PTON] == TRUE) {
//            exit(-3);
//        }
	}

	return addr;
}

/*
 * Name: Connect
 *
 * Prototype:
 *          int Connect(int socket_fd, struct sockaddr *server_addr, int address_len)
 *
 * Description:
 *          Implementation for Connect wrapper
 *
 * Header files:
 *          wrap1cli.h
 *
 */
int Connect(int socket_fd, struct sockaddr *server_addr, int address_len) {

	errno = 0;

	int conn = connect(socket_fd, server_addr, address_len);

	if (conn < 0) {
		perror(ERROR);

//        if (exit_flags[CONNECT] == TRUE) {
//            exit(-4);
//        }
	}

	return conn;
}

/*
 * Name: Fputs
 *
 * Prototype:
 *          int Fputs(const char* recvline, FILE * outfile)
 *
 * Description:
 *          Implementation for Fputs wrapper
 *
 * Header files:
 *          wrap1cli.h
 *
 */
int Fputs(const char* recvline, FILE * outfile) {

	errno = 0;

	int num_chars = fputs(recvline, outfile);

	if (num_chars == EOF) {
		perror(ERROR);

//        if (exit_flags[FPUTS] == TRUE) {
//            exit(-5);
//        }
	}

	return num_chars;
}

/*
 * Name: Close
 *
 * Prototype:
 *          int Close(int socket_fd)
 *
 * Description:
 *          Implementation for Close wrapper
 *
 * Header files:
 *          wrap1cli.h
 *
 */
int Close(int socket_fd) {

	errno = 0;

	int close_value;
	close_value = close(socket_fd);

	if (close_value < 0) {
		perror(ERROR);

//        if (exit_flags[CLOSE] == TRUE) {
//            exit(-6);
//        }
	}

	return close_value;
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
 *          wrap1cli.h
 *
 */
ssize_t Writen(int socket_fd, const void* str, size_t length) {

	errno = 0;

	ssize_t line = writen(socket_fd, str, length);

	if (line < 0) {
		perror(ERROR);

//        if (exit_flags[WRITEN] == TRUE) {
//            exit(-7);
//        }
	}

	return line;
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
 *          wrap1cli.h
 *
 */
ssize_t Readline(int socket_fd, void* str, size_t length) {

	errno = 0;

	ssize_t line = readline(socket_fd, str, length);

	if (line < 0) {
		perror(ERROR);

//        if (exit_flags[READLINE] == TRUE) {
//            exit(-8);
//        }
	}

	return line;
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
 *          wrap1cli.h
 *
 */
char* Fgets(char *s, int size, FILE *stream) {

	errno = 0;

	char* line = fgets(s, size, stream);

	if (line == NULL && errno != 0) {
		perror(FGETS_MSG);

//        if (exit_flags[FGETS] == TRUE) {
//            exit(-9);
//        }
	}

	return line;
}

/*
 * Name: Chdir
 *
 * Prototype:
 *          int Chdir(const char *path)
 *
 * Description:
 *          change dir
 *
 * Header files:
 *          wrap1cli.h
 *
 */
int Chdir(const char *path) {

	int chdir_msg = 0;

	errno = 0;

	chdir_msg = chdir(path);

	if (chdir_msg < 0) {
		perror(ERROR);
	} else {
		// success print message
		printf(LCD_MSG, path);
	}

	return chdir_msg;
}
