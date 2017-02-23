#include <shell_external.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char* env_save;

void save_env(){
	env_save = getenv("PATH");
}
void exec_list(char** token)
{
	if (feof(stdin))
	{        	
		exit_cleanup();
	}
	else if (token[0]== NULL)
	{
		return;
	}
	
	else if(strcmp(token[0], "getpath")== 0)
	{
		if (token[1] != NULL)
		{
			printf("Error: getpath shouldn't have argument\n");
			return;
		}        	

		printf("%s\n", getenv("PATH"));
	}
	else if(strcmp(token[0], "setpath")== 0)
	{
		if (token[1] == NULL || token[2] != NULL)
		{
			printf("Error: setpath has to have only one argument\n");
			return;
		}        	

		setenv("PATH", token[1], 1);
	}
	else if (strcmp(token[0],"exit") == 0)
	{
		if (token[1] != NULL)
		{
			printf("Error: exit shouldn't have arguments\n");
			return;
		}        	
		exit_cleanup();
	}
	else {

	
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
		exit(-1);
    }
    else
    {
        wait(NULL);
    }

}


void exit_cleanup()
{
	setenv("PATH", env_save, 1);
		
	exit(0);
}
