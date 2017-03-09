#include <shell_commands.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "shell_commands.h"

char* env_save;

const command_map commands[COMMAND_AMMOUNT] =
{
	{.name = "getpath", .callback = &get_path}
	,{.name = "setpath", .callback = &set_path}
	,{.name = "cd", .callback = &cd}
	,{.name = "exit", .callback = &exit_shell}
	
};

void save_env()
{
	env_save = getenv("PATH");
}

bool exec_internal(char** token)
{
	if (feof(stdin))
		exit_shell(token);

	if (token[0] != NULL)
    {
        for (uint8_t i = 0; i < COMMAND_AMMOUNT; i++)
            if (strcmp(commands[i].name, token[0]) == 0)
            {
            commands[i].callback(token);
                return true;
                }
    }

    return false;
}

bool exec_external(char** tokenized_command)
{
    __pid_t child_process_id = fork();

    if (child_process_id < 0)
    {
        return false;
    }

    if (child_process_id == 0)
    {    	
        execvp(tokenized_command[0], tokenized_command);
		perror(tokenized_command[0]);
		exit(-1);
    }
    else
    {
        wait(NULL);
		return true;
    }
}

bool get_path(char** parameters)
{
	if (parameters[1] != NULL)
	{
		printf("Error: getpath shouldn't have argument\n");
		return false;
	}

	printf("%s\n", getenv("PATH"));
	return true;
}

bool set_path(char** parameters)
{
	if (parameters[1] == NULL || parameters[2] != NULL)
	{
		printf("Error: setpath has to have only one argument\n");
		return false;
	}

	setenv("PATH", parameters[1], 1);
	return true;
}
bool cd(char** token)
{
	if (token[1] == NULL)
	{
		chdir(getenv("HOME"));
		
	}
	else if (token[2] == NULL)
	{
		
		if(chdir(token[1])==-1)
		{
			perror(token[1]);
		}
	}
	else
	{
		printf("Error: Invalid number of arguments\n");
		return false;

	} 
	return true;
}


bool exit_shell(char** parameters)
{
	if (parameters[1] != NULL)
	{
		printf("Error: exit shouldn't have arguments\n");
		return false;
	}

	setenv("PATH", env_save, 1);
	printf("%s\n", getenv("PATH"));
	exit(0);

	return true;
}

void save_history(char** input, histList* history){
	history->num = (history->num + 1 > 4)? 0 : history->num +1;
	int i;
	for (i = 0; input[i]!= NULL; i++){
		history->command[history->num][i] = strdup(input[i]);
	}
	
	history->command[history->num][i] = NULL;
	
} 

void load_history(char* input_tokens[], histList* history){
	printf("%s\n", history->command[history->num][0]);
	int i;
	for (i = 0; history->command[history->num][i]!= NULL; i++){
		input_tokens[i] = history->command[history->num][i];
	}
	input_tokens[i] = NULL;
}


