
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

#include <readline/readline.h>
#include <readline/history.h>

#include "include/get_command.h"
#include "config.h"


int parse(char *buf,char ***args)
{
  int argc=0;
  while(*buf!='\0')
  {
    while(*buf== ' '  || *buf=='\t' )
    {
      *buf='\0';
      buf++;
    }
    
    
    *args=(char**)realloc(*args,sizeof(char *)*(argc+1));
    argc++;
    
    (*args)[argc-1]=buf;
    while(*buf!=' ' && *buf!='\t' && *buf!='\0')
    buf++;
  }
  
   *args=(char**)realloc(*args,sizeof(char *)*(argc+1));
   (*args)[argc]=NULL;
   
  return argc;
}


int execute_fg(char **args)
{
  int pid;
  int status;
  
  
  pid=fork();
  
  if(pid<0)
  {
    perror("fork ");
    return -1;
  }
  
  else if (pid==0)
  {
   
    if(execvp(args[0],args)==-1)
    {
      fprintf(stderr,"µSH : %s " ,args[0]);
      perror(" ");
      exit(EXIT_FAILURE);
    }
    
  }
  
  else 
  {
    //waitpid(pid,&status,0);
    while(wait(&status)!=pid);
    printf("\nProgram exited with code : %d \n",status);
  }
  
  return 0;
}


void cambiar_dir(char **args)
{
 if( chdir(args[1])==-1)
 {
   perror("cd ");
 }
}

int main(int argc, char **argv) {
  
  char **args=NULL;
  char buf[1024];
  char *buf_command=NULL;
  char *comand=NULL;
  int i=0;
  int res;
  long unsigned int l=0; //memeria reservada al buffer
    
    //activamos el historial en readline
    
    using_history();
    read_history("/home/abdel/projects/mush/historial");
 
   
   printf("Bienvenido a µSH version %d.%d\n",VERSION_MAJOR,VERSION_MINOR);
   
   while(1)
   {
     sprintf(buf,"µSH @ %s ]> ",get_current_dir_name());
     
    
     do{
    // get_command(buf);
    free(comand);
    
    buf_command=readline(buf);
    
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
    //añadimos el comando al historial
     add_history(comand);
    
     
     l=parse(comand,&args);
     
    
     
     
     
     if(args[0]==NULL)
     {
       ;
     }
     else if(!strcmp(args[0],"cd"))
     {
       cambiar_dir(args);
     }
     else if(!strcmp(args[0],"exit"))
     {
       write_history("/home/abdel/projects/mush/historial");
       printf("\n Goodbye!!\n");
      exit(0);
       
     }
     else if(args!=NULL)
     {
       execute_fg(args);
     }
     
   }
   
   
    
    return 0;
}

