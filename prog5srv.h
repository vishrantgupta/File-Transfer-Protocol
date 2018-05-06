/********************************************************************

 prog5srv.h

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=2

 *********************************************************************/

#ifndef PROG5_H
#define PROG5_H

#include "wrap5srv.h"

//#define MAXLINE 1024
#define CMD 0

// arg 1 index
#define ARG1 1

// agr 2 index
#define ARG2 2

// space
#define SPACE " "

// pwd output
#define PWD_OUTPUT "%d:\"%s\" is current directory.\n"

// cd output
#define CD_OUTPUT "%d:CWD command successful.\n"

// error output
#define ERROR_OUTPUT "%d:\n"

// cdup command
#define CDUP_COMMAND ".."

// zero message
#define ZERO '0'

// blank
#define BLANK ""

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
 *          prog5cli.h
 */
void str_echo(int);

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
 *          prog5srv.h.c
 *
 */
cmd_id get_args(char *, char *, char *, char *);

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
 *          prog5srv.h.c
 *
 */
cmd_id find_id(char *);

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
 *          prog5srv.h.c
 *
 */
bool new_dir(char *);

// socket address struct
#define SA struct sockaddr

// default port
#define DEFAULT_PORT 9880

// number of connections
#define LISTENQ 15

// user home
#define USER_HOME "~"

// backslash zero
#define BACKSLASH_ZERO '\0'

// backslash n
#define BACKSLASH_N '\n'

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
void signal_handler(int signal_number);

//#define LISTENQ 15

#endif
