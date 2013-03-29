#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <unistd.h>
#include <termios.h>

extern  last[100];
extern char **history;
extern int h_size;

void add_to_hist(char *s);
int getch();
void get_command(char *s);