#include <commands.h>
#include <builtin.h>
#include <parser.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include <unistd.h>

#define OUTPUT 0
#define INPUT 1

int in=STDIN_FILENO;
int out=STDOUT_FILENO;

int tuberia[2];

void conect_pipe_output_to_stdin(int p[2])
{
  close(STDIN_FILENO);
  dup(p[OUTPUT]);
  close(p[OUTPUT]);
}

void conect_pipe_input_to_stdout(int p[2])
{
  close(STDOUT_FILENO);
  dup(p[INPUT]);
  close(p[INPUT]);
}

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



int eval_cmd(char **args,int argc)
{
  int pid;
  
  if (argc==0)
  {
    //Nothing to do
    
    return 0;
    
  }
  
 
  
 //is a shell command? 
if(!execute_builtins(argc,args))
{
  ;
}
     
  //not a shell command
  
  else if(!strcmp(args[argc-1],"&"))
  {
    //free(args[argc-1]);
    args[argc-1]=NULL;
    pid=execute_bg(args);
    
    if(pid>0)
    {
      printf("Program executed with pid : %d\n",pid);
    }
    
  }
  
  else 
  {
    execute_fg(args);
  }
  
  return 0;

}


