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

#ifndef WRAP5_H_CLI
#define WRAP5_H_CLI

#include    "/home/cs631/common/config.h"
#include    "/home/cs631/common/in-out.h"

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/socket.h>
#include    <stdlib.h>
#include    <arpa/inet.h>
#include    <stdbool.h>

/* Name: Socket
 *
 * Prototype:
 *          int Socket(int family, int type, int protocol)
 *
 * Description:
 *          This function is a wrapper for system call socket, it creates an end point for the commnunication.
 *
 * Header files:
 *          wrap1cli.h
 */
int Socket(int family, int type, int protocol);

/* Name: Fputs
 *
 * Prototype:
 *          int Fputs(const char* recvline, FILE *)
 *
 * Description:
 *          Wrapper for fput, it writes string to stream
 *
 * Header files:
 *          wrap1cli.h
 */
int Fputs(const char* recvline, FILE *);

/* Name: Inet_pton
 *
 * Prototype:
 *          int Inet_pton(int family, const char *strptr, void *addrptr)
 *
 * Description:
 *          Wrapper for inet_pton, convert IPv4 and IPv6 addresses from text to binary form
 *
 * Header files:
 *          wrap1cli.h
 */
int Inet_pton(int family, const char *strptr, void *addrptr);

/* Name: Connect
 *
 * Prototype:
 *          int Connect(int socket_fd, struct sockaddr *serv_addr, int addrlen)
 *
 * Description:
 *          Wrapper for Connect, initiate a connection on a socket
 *
 * Header files:
 *          wrap1cli.h
 */
int Connect(int socket_fd, struct sockaddr *serv_addr, int addrlen);

/* Name: Close
 *
 * Prototype:
 *          int Close(int socket_fd)
 *
 * Description:
 *          Wrapper for close, it closes a file descriptor
 *
 * Header files:
 *          wrap1cli.h
 */
int Close(int socket_fd);

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
ssize_t Writen(int, const void*, size_t);

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
ssize_t Readline(int, void*, size_t);

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
int Chdir(const char *path);

#endif
