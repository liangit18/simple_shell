CC := gcc

CFLAGS := -Wall -Werror -g

HEADER := simple_shell.h

SOURCES :=shell_main.c

all: $(SOURCES)
	$(CC) $(CFLAGS) -o mysh $(SOURCES)
