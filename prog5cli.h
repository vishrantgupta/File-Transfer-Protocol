/********************************************************************

 prog5cli.f

 Class:     CSCI 631 Network Applications Programming
 Program:   Assignment 5
 Author:    Vishrant K Gupta
 Z-number:  z1815637
 Date Due:  04/28/17

 Purpose:   FTP

 Execution: Make execute N=5 T=1

 *********************************************************************/

#ifndef PROG5CLI_H_
#define PROG5CLI_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>

#include "util5cli.h"
#include <wordexp.h>

#include "/home/cs631/common/in-out.h"

#define DEFAULT_PORT 9880

//#define MAXLINE 1024
#define CMD 0

// arg 1 index
#define ARG1 1

// agr 2 index
#define ARG2 2

// not connected message
#define NOT_CONNECTED "Not connected.\n"

// prompt
#define PROMPT "ftp> "

// already connected
#define ALREADY_CONNECTED "Already connected to %s, use close first.\n"

// good bye
#define GOODBYE "Goodbye.\n"

// invalid command
#define INVALID_CMD "?Invalid command\n"

// error
#define ERROR "Error"

// local message
#define LCD_MSG "Local directory now %s\n"

// space
#define SPACE " "

// user home
#define USER_HOME "~"

// backslash zero
#define BACKSLASH_ZERO '\0'

// backslash n
#define BACKSLASH_N '\n'

// help
#define HELP_CMD "%s: %s\n"

// help invalid command
#define HELP_INVALID "help: no help topics match `%s'.  Try `help'\n"

// connected message
#define CONNECTED_MSG "Connected to %s.\n"

// inet pton message
#define INET_PTON_MSG "ftp: %s: Name or service not known\n"

// ignore server error index
#define IGNORE_SUCCUESS_CODE 2

// open message
#define OPEN_MSG "usage: open host-name [port]\n"

// to message
#define TO_MSG "(to) "

// cd message
#define CD_MSG "(remote-directory) "

// cd usage
#define CD_USAGE "usage: cd remote-directory\n"

// zero message
#define ZERO '0'

// new line
#define NEWLINE "\n"

#define FGETS_MSG "Error while reading from stream\n"

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
 *          prog5cli.h
 *
 */
bool client(char* ip_address, char* server_port, bool prompt);

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
 *          prog5cli.h
 *
 */
bool str_cli(int sockfd, char* saddr, bool prompt);

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
void str_echo(int sockfd, char* command);

#endif /* PROG5CLI_H_ */
