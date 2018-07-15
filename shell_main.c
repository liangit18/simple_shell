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

		if(position>=count*SHELL_RL_BUFFSIZE){
			count+=1;
			buffer=realloc(buffer,count*SHELL_RL_BUFFSIZE);
			if(!buffer){
				fprintf(stderr,"sshell:malloc error\n");
				exit(EXIT_FAILURE);
			}
		}
	}

}

char** shell_split_line(char* line){
	int count=1,position=0;
	char* token;
	char** tokens;

	tokens=malloc(sizeof(char*)*SHELL_TOK_BUFFSIZE);
	if(!tokens){
		fprintf(stderr, "malloc error\n" );
		exit(EXIT_FAILURE);
	}

	token=strtok(line,SHELL_TOK_DELIM);
	while(token){
		tokens[position]=token;
		position++;

		if(position>=count*SHELL_TOK_BUFFSIZE){
			count+=1;
			tokens=realloc(tokens,count*SHELL_TOK_BUFFSIZE);
			if(!tokens){
				fprintf(stderr, "realloc error\n");
				exit(EXIT_FAILURE);
			}
		}

		token=strtok(NULL,SHELL_TOK_DELIM);
	}
	tokens[position]=NULL;

	return tokens;
}

int main(int argc,char** argv){

	shell_loop();
	return EXIT_SUCCESS;
}

void shell_loop(){
	char* line;
	char** args;
	int status=0;

	do{
		printf("> ");
		line=shell_read_line();
		printf("%s\n",line );
		args=shell_split_line(line);

		//Debug code//
		char** temp=args;
		while(* temp){
			printf("%s\n", * temp);
			temp+=1;
		}
		//status=shell_execut(args);

		free(line);
		free(args);
	}while(status);
}
