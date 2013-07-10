#include <commands.h>
#include <builtin.h>
#include <parser.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include <unistd.h>

#define READ_END 0
#define WRITE_END 1


int execute_fg(char *cmd)
{
  int pid;
  int status;
  pid=execute_bg(cmd);
  
  if(pid>0)
  {
    waitpid(pid,&status,0);
   
    //printf("\nProgram exited with code : %d \n",status);
    
    return 0;
  }
  
  else return -1;
}



int execute_bg(char *cmd)
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
   
   ejecutar(cmd);
    
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
    
    int pid2=fork();
    
    if(pid2==0)
    {
      close(p[WRITE_END]);
      close(STDIN_FILENO);
      dup(p[READ_END]);
      eval_cmd(cmd2);
    
      exit(-1);
    }
    else if(pid2<0)
    {
      perror("fork");
    }
    
    else 
    {
      
      waitpid(pid,NULL,0);
     
      
      exit(0);
      
    }
   
   
  }
  
  else 
  {
    
    
      char **args=NULL;
      parse(cmd,&args);
      
      execvp(args[0],args);
      perror("execvp");
      free(args);
      exit(EXIT_FAILURE);
      
      
    
  }
  
  
  
  return 0;
}



int eval_cmd(char *cmd)
{
  /*int pid=fork();
  
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
 
waitpid(pid,NULL,0);*/
  
  char **args=NULL;
  char *cmd2=(char *)malloc(strlen(cmd)+1);
  
  memcpy(cmd2,cmd,strlen(cmd)+1);
  
  int argc=  parse(cmd2,&args);
  
 if(execute_builtins(argc,args)==0)
 {
   ;
 }
 
 else  if(cmd[strlen(cmd)-1]=='&')
 {
   cmd[strlen(cmd)-1]=0;
   execute_bg(cmd);
 }
 else
 {
  execute_fg(cmd);
 }
 return 0;
 
}


