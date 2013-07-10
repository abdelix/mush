#include <commands.h>
#include <builtin.h>
#include <parser.h>
#include <command_type.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include <unistd.h>

#define READ_END 0
#define WRITE_END 1


int execute_fg(char **args)
{
  int pid;
  int status;
  pid=execute_bg(args);
  
  if(pid>0)
  {
    waitpid(pid,&status,0);
   
    printf("\nProgram exited with code : %d \n",status);
    
    return 0;
  }
  
  else return -1;
}



int execute_bg(char **args)
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
  
 
  
  return pid;
}



int ejecutar(char *cmd)
{
   char *cmd2=strchr(cmd,'|');
  
  int p[2];
  
  if(cmd2!=NULL)
  {
   *cmd2=0;
   cmd2++;
   
   pipe(p);
   
   int pid=fork();
    if(pid==0)
    {
      close(p[READ_END]);
      close(STDOUT_FILENO);
      dup(p[WRITE_END]);
      
      eval_cmd(cmd);
      exit(0);
    }
    else if(pid<0)
    {
      perror("fork");
      return -1;
    }
    
    close(p[WRITE_END]);
    close(STDIN_FILENO);
    dup(p[READ_END]);
    eval_cmd(cmd2);
    
    waitpid(pid,NULL,0);

   
   
  }
  
  else 
  {
      char **args=NULL;
      parse(cmd,&args);
      
      execvp(args[0],args);
      perror("execvp");
      exit(EXIT_FAILURE);
    
  }
  
  
  
  return 0;
}



int eval_cmd(char *cmd)
{
  int pid=fork();
  
  if(pid==0)
  {
    ejecutar(cmd);
    exit(-1);
  }
  
 else if (pid<0)
 {
   perror("eval_cmd:fork");
   return -1;
 }
 
waitpid(pid,NULL,0);
 
 return 0;
 
}


