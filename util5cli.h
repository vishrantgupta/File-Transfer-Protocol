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

#ifndef UTIL5CLI_H_
#define UTIL5CLI_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>

#include <wordexp.h>

#include "prog5cli.h"

// command ip enum
typedef enum cmd_id {
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
 *          wrap1cli.h
 *
 */
cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2);

/*
 * Name: prnt_cmd_help
 *
 * Prototype:
 *          void prnt_cmd_help()
 *
 * Description:
 *          print perticular cmd help
 *
 * Header files:
 *          wrap1cli.h
 *
 */
void prnt_cmd_help(char* cmd);

/*
 * Name: prnt_cmd_list
 *
 * Prototype:
 *          void prnt_cmd_list()
 *
 * Description:
 *          print all list of help
 *
 * Header files:
 *          wrap1cli.h
 *
 */
void prnt_cmd_list();

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
 *          wrap1cli.h
 *
 */
void trim(char* str);

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
 *          wrap1cli.h
 *
 */
cmd_id find_id(char* cmd);

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
 *          wrap1cli.h
 *
 */
bool new_dir(char* dir, cmd_id id, int socket_fd);

/*
 * Name: not_connected
 *
 * Prototype:
 *          void not_connected()
 *
 * Description:
 *          for printing not connected message
 *
 * Header files:
 *          wrap1cli.h
 *
 */
void not_connected();

#endif /* UTIL5CLI_H_ */
