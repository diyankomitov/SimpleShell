#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shell_commands.h>
#include <shell_alias.h>
#include <shell_input.h>
#include <shell_history.h>

char* env_save;

const command_map commands[COMMAND_AMOUNT] =
{
	{.name = "getpath", .callback = &get_path}
	,{.name = "setpath", .callback = &set_path}
	,{.name = "cd", .callback = &cd}
	,{.name = "exit", .callback = &exit_shell}
	,{.name = "history", .callback = &print_history}
	,{.name = "alias", .callback = &alias}
	,{.name = "unalias", .callback = &remove_alias}
};

void save_env()
{
	env_save = getenv("PATH");
}

bool exec_internal(char** token)
{
	if (token[0] != NULL)
    {
        for (uint8_t i = 0; i < COMMAND_AMOUNT; i++)
        {
        	if (strcmp(commands[i].name, token[0]) == 0)
            {
				commands[i].callback(token);
				return true;
			}
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

bool cd(char** parameters)
{
	if (parameters[2] == NULL)
	{
        char* dir = (parameters[1] == NULL)? getenv("HOME") : parameters[1];
		
		if(chdir(dir) == -1)
		{
			perror(parameters[1]);
		}
	}
	else
	{
		printf("Error: Invalid number of arguments\n");
		return false;

	} 
	return true;
}

bool alias(char** parameters)
{
    if (parameters[1] == NULL)
    {
        print_aliases();
        return true;
    }
    else
    {
        if (parameters[2] != NULL)
            return add_alias(parameters);
        else
        {
            printf("Error: command not specified for the alias\n");
            return false;
        }
    }
    return false;
}

bool exit_shell(char** parameters)
{
	if (parameters[1] != NULL)
	{
		printf("Error: exit shouldn't have arguments\n");
		return false;
	}
	chdir(getenv("HOME"));
	save_history();

	save_aliases();
	setenv("PATH", env_save, 1);
	printf("%s\n", getenv("PATH"));
	exit(0);

	return true;
}
