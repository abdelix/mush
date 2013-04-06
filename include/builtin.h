/*  builtin.h 
 * 
 * 
 * Copyright 2013 abdel <abdel.14@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/*
 * Contiene las funciones que implementa el shell
 * 
 * 
 * 
 */

/*************************************************/
#ifndef __MUSH_BUILTIN_H__
#define __MUSH_BUILTIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/*
 * 
 * if args[0] is internal command exeutes it and return 0 otherwise return -1
 * 
 * */
int execute_builtins(int argc,char ** args);

/*
 * Simple change directory command  
 * Note : only args[0] is used as the dir path
 * 
 * @param : args list or arguments (only args[0] i used for now)
 * @return : 
 * 
 * */
void  change_dir(int argc,char **args);

/*
 * 
 * comando history
 * 
 */
void mush_history(int argc,char **args);
/*
 * Show the whole history
 * 
 */
void show_history();


/*
 * Exits the shell
 * 
 */

void mush_exit(int argc,char **args);


#endif