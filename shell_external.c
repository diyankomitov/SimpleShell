#include <shell_external.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void exec_list(char** token){
	if(strcmp(token[0], "getpath")== 0){
		char* path = getenv("PATH");
		printf("%s\n", path);
	}
	else if(strcmp(token[0], "setpath")== 0){
		setenv("PATH", token[1], 0);
	}
	else{
        exec_external(token);
	}
}

void exec_external(char** tokenized_command)
{
    __pid_t child_process_id = fork();

    if (child_process_id < 0)
        return;

    if (child_process_id == 0)
    {    	
        execvp(tokenized_command[0], tokenized_command);
		perror(tokenized_command[0]);
    }
    else
    {
        wait(NULL);
    }

}
