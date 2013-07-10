/*  builtin.c 
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


#include <builtin.h>
#define NO_BLTIN_FNS 3
const char *builtin_fns_name[NO_BLTIN_FNS]={"cd","exit","history"};

void (*bltin_fns[NO_BLTIN_FNS])()={&change_dir,&mush_exit,&mush_history};

int execute_builtins(int argc,char ** args)
{
  int i=0;
  while(i<NO_BLTIN_FNS && strcmp(*args,builtin_fns_name[i])  )
  {
    i++;
  }
  
  if(i<NO_BLTIN_FNS)
  {
    (bltin_fns[i])(argc,args);
    return 0;
  }
  //not a builtin
  return -1;
  
}


void mush_exit(int argc,char **args)
{
    write_history("/home/abdel/projects/mush/historial");
    printf("\n Goodbye!!\n");
    exit(0);
	
}
void change_dir(int argc,char **args)
{
 if( chdir(args[1])==-1)
 {
   perror("cd ");
 }
}



void show_history()
{
  HIST_ENTRY *entry;
  int i=1;
  while((entry=history_get(i))!=NULL)
  {
    printf("%d)%s\n",i,entry->line);
    i++;
  }
}


void mush_history(int argc,char **args)
{
  if(argc>2)
  {
    printf("history : too many arguments\n");
    
  }
  
  else if(argc==1)
  {
    show_history();
  }
  else if(strcmp(args[1],"-c")==0)
  {
    clear_history();
  }
  
  else 
  {
    printf("history : unrecognized argument \"%s\"\n",args[1]);
  }
  
  
}