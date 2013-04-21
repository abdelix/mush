
/*  main.c 
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
#include <signal.h>
/*
 * Biblioteca readline para leer comandos :
 * -Facil edicion estilo vim
 * -historial
 * ... 
 * -la usada por bash
 */
#include <readline/readline.h>
#include <readline/history.h>

//#include "include/get_command.h"
#include "config.h"
#include "include/parser.h"
#include "include/commands.h"


int tub[2];
 
 
 void child_end(int x)
 {
   int pid=0;
   int status;
   
   pid=waitpid(0,&status,WNOHANG);
  if(pid>0)
  {
   printf("\nProcces [%d] ended with code :%d\n",pid,status);
  }
   signal(SIGCHLD,&child_end);
 }



int main(int argc, char **argv) {
  
  char **args=NULL;
  char prompt[1024];
  char *buf_command=NULL;
  char *comand=NULL;
  int i=0;
  int res;
  long unsigned int l=0; //cantidad de argumentos
    
    
      signal(SIGCHLD,&child_end);
    
    //activamos el historial en readline
    
    using_history();
    read_history("/home/abdel/projects/mush/historial");
  /*
   * MENSAJE DE BIENVENIDA
   * 
   */
   printf("Bienvenido a µSH version %d.%d\n",VERSION_MAJOR,VERSION_MINOR);
   
   
   /*
    * 
    * BUCLE PRINCIPAL
    * 
    */
   
   while(1)
   {
     sprintf(prompt,"µSH @ %s ]> ",get_current_dir_name());
     
    
     do{
       /*
	* Liberamos la memoria anteriormente reservada si co
	*/

       free(comand);
       free( buf_command);
       
      
       buf_command=readline(prompt);
    
    
       //efectuamos expansiones de expresiones del historial
       res=history_expand(buf_command,&comand);
    
       switch(res)
       {
      
	 //mostramos el resultado de la expansion si esta a tenido lugar
      
	 case 1:
	
	   printf("%s\n",comand);
	
	   break;
      
	 case -1 :
	
	   fprintf(stderr,"Error en la expansion : %s\n",comand);
	
	   break;
     
	 default:
	   ;
      
      
	 
      }
     
    }while(res==-1);
    
    //añadimos el comando la lista del historial 
    add_history(comand);
    
    //analizamos el comando
    
    args=NULL;
    l=parse(comand,&args);
    
    eval_cmd(args,argc);
    //interpretamos el comando
    //eval_cmd(args,l);
    free(args);
    
    
    
    //child_end(0);
    
  }//while(1) 
   
    
    return 0;
}

