#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHELL_RL_BUFFSIZE	1024
#define SHELL_TOK_BUFFSIZE	64

#define SHELL_TOK_DELIM		" \t\r\n\a"

void shell_loop();