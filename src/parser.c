#include <parser.h>


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