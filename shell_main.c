#include "simple_shell.h"

int (*builtin_func[])(char**)={
	&shell_cd,
	&shell_help,
	&shell_exit
};

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

int shell_num_builtins(){
	return sizeof(builtin_str)/sizeof(char*);
}

int shell_launch(char** args){
	int status=0;
	pid_t pid;

	pid=fork();
	if(pid<0){
		perror("mysh:");
	}
	else if(pid==0){
		if(execvp(args[0],args)==-1){
			perror("mysh:");
		}
	}
	else{
		do{
			waitpid(pid,&status,WUNTRACED);
		}while(!WIFEXITED(status)&&!(WIFSIGNALED(status)));
	}
	return 1;
}

int shell_cd(char** args){
	if(args[1]==NULL){
		fprintf(stderr, "mysh: expected argument to \"cd\"\n" );
	}
	else{
		if(chdir(args[1])!=0){
			perror("mysh:");
		}
	}

	return 1;
}

int shell_help(char** args){
	int i=0;

	printf("Simple shell\n");
	printf("Type program names and argument\n");

	printf("The following are built in:\n");
	while(i<shell_num_builtins()){
		printf("	%s\n", builtin_str[i]);
		i+=1;
	}
	return 1;
}

int shell_exit(char** args){
	return EXIT_SUCCESS;
}

int shell_execut(char** args){
	int i=0;

	if(args[0]==NULL){
		return 1;
	}

	while(i<shell_num_builtins()){
		if(strncmp(args[0],builtin_str[i],sizeof(args[0])/sizeof(char))==0){
			return (*builtin_func[i])(args);
		}
		i+=1;
	}

	return shell_launch(args);
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

		//Debug code//
		//printf("%s\n",line );
		
		args=shell_split_line(line);

		//Debug code//
		char** temp=args;
		while(* temp){
			printf("%s\n", * temp);
			temp+=1;
		}
		printf("\n");
		
		status=shell_execut(args);

		free(line);
		free(args);
	}while(status);
}
