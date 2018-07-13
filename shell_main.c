#include "simple_shell.h"

char* shell_read_line(){
	int c,position=0;
	
	char* buffer=(char*)malloc(sizeof(char)*SHELL_RL_BUFFSIZE);
	if(!buffer){
		fprintf(stderr, "sshell:malloc error\n" );
		exit(EXIT_FAILURE);
	}

	while(true){
		
	}

}

int main(int argc,char** argv){

	shell_loop();
	return EXIT_SUCCESS;
}

void shell_loop(){
	char* line;
	char** args;
	int status;

	do{
		printf("> ");
		line=shell_read_line();
		args=shell_split_line();
		status=shell_execut(args);

		free(line);
		free(args);
	}while(status);
}
