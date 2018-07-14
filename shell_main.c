#include "simple_shell.h"

char* shell_read_line(){
	int c,count=1,position=0;
	
	char* buffer=(char*)malloc(sizeof(char)*SHELL_RL_BUFFSIZE);
	if(!buffer){
		fprintf(stderr, "sshell:malloc error\n" );
		exit(EXIT_FAILURE);
	}

	while(true){
		c=getchar();

		if(c==EOF||c=='\n'){
			buffer[position]='\0';
			return buffer;
		}
		else{
			buffer[position]=c;
			position+=1;
		}

		if(position>=SHELL_RL_BUFFSIZE){
			count+=1;
			buffer=realloc(buffer,count*SHELL_RL_BUFFSIZE);
			if(!buffer){
				fprintf(stderr,"sshell:malloc error\n");
				exit(EXIT_FAILURE);
			}
		}
	}

}

int main(int argc,char** argv){

	shell_loop();
	return EXIT_SUCCESS;
}

void shell_loop(){
	char* line;
	//char** args;
	int status=0;

	do{
		printf("> ");
		line=shell_read_line();
		printf("%s\n",line );
		//args=shell_split_line();
		//status=shell_execut(args);

		free(line);
		//free(args);
	}while(status);
}
