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