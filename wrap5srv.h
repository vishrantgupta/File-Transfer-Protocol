/********************************************************************

 wrap5srv.h

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=2

 *********************************************************************/

#ifndef WRAP5_H_SRV
#define WRAP5_H_SRV

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include <stdbool.h>
#include<netinet/ip.h>
#include<signal.h>
#include <wordexp.h>

//enum datatype
typedef enum {
	NEG_ = -1,
	ZERO_,
	QM_,
	BYE_,
	CD_,
	CDUP_,
	CLOSE_,
	DISCONNECT_,
	HELP_,
	LCD_,
	OPEN_,
	PWD_,
	QUIT_
} cmd_id;

//exit flags constants definition
#define NO_OF_FUNCTIONS  13

// listen function
#define LISTEN 1

// socket function
#define SOCKET 2

// bind function
#define BIND 3

// accept function
#define ACCEPT 4

// close function
#define CLOSE 5

// writen function
#define WRITEN 6

// readline function
#define READLINE 7

// fork function
#define FORK 8

// getcwd function
#define GETCWD 9

// wait function
#define WAIT 10

// signal function
#define SIGNAL 11

// chdir function
#define CHDIR 12

// fgets function
#define FGETS 13

// error
#define ERROR "Error"

// fork error
#define FORK_ERROR "Error while creating child process value is %d\n"

// wait error
#define WAIT_ERROR "Process %d exited, status = %d\n"

/*
 * Name: Listen
 *
 * Prototype:
 *          int Listen(int socket_fd, int backlog)
 *
 * Description:
 *          Wrapper for system call Listen
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Listen(int socket_fd, int backlog);

/*
 * Name: Socket
 *
 * Prototype:
 *          int Socket(int domain, int type, int protocol)
 *
 * Description:
 *          Wrapper for system call Socket
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Socket(int domain, int type, int protocol);

/*
 * Name: Accept
 *
 * Prototype:
 *          int Accept(int socket_fd, struct sockaddr *address, socklen_t *addr_len)
 *
 * Description:
 *          Wrapper for system call Accept
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Accept(int socket_fd, struct sockaddr *address, socklen_t *addr_len);

/*
 * Name: Bind
 *
 * Prototype:
 *          int Bind(int socket_fd, const struct sockaddr *address, socklen_t addr_len)
 *
 * Description:
 *          Wrapper for system call Bind
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Bind(int socket_fd, const struct sockaddr *address, socklen_t addr_len);

/*
 * Name: Close
 *
 * Prototype:
 *          int Close(int file_desc)
 *
 * Description:
 *          Wrapper for system call close
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Close(int file_desc);

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
 *          wrap5srv.h
 *
 */
int Fork();

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
 *          wrap5srv.h
 *
 */
ssize_t Readline(int, void*, size_t);

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
 *          wrap5srv.h
 *
 */
ssize_t Writen(int, const void*, size_t);

/*
 * Name: Fgets
 *
 * Prototype:
 *          char* Fgets(char *s, int size, FILE *stream)
 *
 * Description:
 *          Read data from stream
 *
 * Header files:
 *          wrap1cli.h
 *
 */
char* Fgets(char *s, int size, FILE *stream);

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
 *          wrap5srv.h
 *
 */
pid_t Wait(int *wstatus);

/*
 * Name: Sigfunc
 *
 * Prototype:
 *          void Sigfunc(int)
 *
 * Description:
 *          Sigfunc
 *
 * Header files:
 *          wrap5srv.h
 *
 */
typedef void Sigfunc(int);

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
 *          wrap5srv.h
 *
 */
Sigfunc *Signal(int signo, Sigfunc *func);

/*
 * Name: Chdir
 *
 * Prototype:
 *          int Chdir(const char *)
 *
 * Description:
 *          Change directory
 *
 * Header files:
 *          wrap5srv.h
 *
 */
int Chdir(const char *);

/*
 * Name: Getcwd
 *
 * Prototype:
 *          char *Getcwd(char *, size_t)
 *
 * Description:
 *          get current working directory
 *
 * Header files:
 *          wrap5srv.h
 *
 */
char *Getcwd(char *, size_t);

#endif
