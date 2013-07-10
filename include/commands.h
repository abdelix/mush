/*  commands.h 
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#include <readline/readline.h>
#include <readline/history.h>


#ifndef  __COMMANDS_H__ 
#define __COMMANDS_H__ 

/*
 * Executes a command in foreground
 * 
 * @param : args list of arguments
 * @return: 0 on succes , -1 on failure
 * 
 */
int execute_fg(char **args);

/*
 * Executes a command in background
 * 
 * @param : args list of arguments
 * @return: 0 on succes , -1 on failure
 * 
 */
int execute_bg(char **args);



int eval_cmd(char *cmd);

#endif