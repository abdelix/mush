/*  get_command.c 
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

#include "../include/get_command.h"
 char **history;
 int h_size;


void add_to_hist(char *s)
{
  int i=0;
  history=(char **)realloc(history,sizeof(char*)*(h_size+1));
  history[h_size]=NULL;

  for(i=h_size;i>0;i--)
  {
    history[i]=history[i-1];
  }
  
  history[0]=(char *)malloc(sizeof(char )*(strlen(s)+1));
  
  strcpy(history[0],s);
  
  h_size++;
  
}

//Funcion que emula laclásica getch de conio.h
int getch()
{
  int tty_fd;
  int c;
  struct termios cfg_vieja;
  struct termios cfg_nueva;
  
  //Sacamos la configuracion de terminal vigenete
  tcgetattr(STDIN_FILENO,&cfg_vieja);
  cfg_nueva=cfg_vieja;
  
  //habilitamos modo no caónico la entrada se pasa 
  //directamene sin esprer enter y hacemos que no
  //se muestre la entrada por pantalla
  cfg_nueva.c_lflag&=~(ICANON|ECHO);
  
  //aplicamos la nueva configuracion
  tcsetattr(STDIN_FILENO,0,&cfg_nueva);
  
  //extraemos un caracter de la entrada
  c=fgetc(stdin);
  //dejamos el terminal como lo encontramos
  tcsetattr(STDIN_FILENO,0,&cfg_vieja);
  
  return c;
  
}

void get_command(char *s)
{
  s[0]='\0';
  char c=0;
  char c1=0;
  int i=0;
  int pos=-1;
  while(c!='\n')
  {
       //imprimimos el buffer
    printf("\r%80c",' ');
    
    printf("\rµSH @ %s ]>%s",get_current_dir_name(),s);
    
    
    c1=c;
    c=getch();
   //   printf("%x-%x-",'\b',c);
    
    //si se ha tenido un 0x1b y luego '[' -> caracter especial :
    //flechas,...
    if(c1=0x1b && c=='[')
    {
      c=getch();
      
      // Funcionalidades de las flechas
      //
      switch(c)
      {
	case 'A' :
	 // printf("[^]");
	  if(pos<h_size-1)
	 {
	   pos++;
	   strcpy(s,history[pos]);
	    i=strlen(s);
	 }
	 
	
	
	  break;
	case 'B' :
	 // printf("[↓]");
	 
	 if(pos>0 )
	 {
	   pos--;
	   strcpy(s,history[pos]);
	   i=strlen(s);
	 }
	 
	 
	 
	  break;
	case 'C' :
	  printf("[→]");
	  break;
	case 'D' :
	  printf("[←]");
	  break;
	  
	default :
	  printf("[unk]");
	  
	
      }
      
    }
    
    //manejamos el borrado lla que en modo no canónico esto no 
    //se hace automaticamente
    else if(i!=0&&(c=='\b' || c==0x7f ))
    {
      s[i-1]='\0';
      i--;
    }
    //lo añadimos al buffer si es impimible y no enter
    else if((isprint(c)||isspace(c))&&c!='\n')
    {
     sprintf(s,"%s%c",s,c);
     
     i++;
    }
    
 
  }
  putchar('\n');
  add_to_hist(s);;
}

