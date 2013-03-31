#include <commands.h>

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

int eval_cmd(char **args)
{
  
  if (args==NULL)
  {
    //Nothing to do
    
    return 0;
    
  }
  
 //is a shell command? 
if(!strcmp(args[0],"history"))
     {
       show_history();
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
	  //not a shell command
	  else 
	  {
	    execute_fg(args);
	  }
  return 0;

}