#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHELL_RL_BUFFSIZE	1024
#define SHELL_TOK_BUFFSIZE	64

#define SHELL_TOK_DELIM		" \t\r\n\a"

char* builtin_str[]={"cd","help","exit"};

void shell_loop();

int shell_cd(char** args);
int shell_help(char** args);
int shell_exit(char** args);