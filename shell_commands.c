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
histList history;

const command_map commands[COMMAND_AMMOUNT] =
{
	{.name = "getpath", .callback = &get_path}
	,{.name = "setpath", .callback = &set_path}
	,{.name = "cd", .callback = &cd}
	,{.name = "exit", .callback = &exit_shell}
	,{.name = "history", .callback = &print_history}
};

void save_env()
{
	env_save = getenv("PATH");
}

void load_history()
{
	history.num = 0;
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

void save_to_history(char** input_tokens){
	history.num = (history.num + 1 > HIST_LEN)? 1 : history.num +1;
	int i;
	for (i = 0; input_tokens[i]!= NULL; i++){
		history.command[history.num][i] = strdup(input_tokens[i]);
	}
	
	history.command[history.num][i] = NULL;
	printf("history.num on save: %d\n", history.num);
} 

void load_from_history(char* input_tokens[])
{
	if(input_tokens[1] != NULL)
	{
		printf("Error: invocation from history can't have any arguments\n");
		return;
	}

	uint8_t number = history.num;

	if (strcmp(input_tokens[0], "!!") == 0 || strcmp(input_tokens[0], "!-0") == 0)
	{
		number = history.num;
	}
	else if (input_tokens[0][1] == '-')
	{
		char temp[3];
		memcpy(temp, &input_tokens[0][2], 2);
		temp[3] = '\0';

		uint8_t tempnum = atoi(temp);

		if (strlen(input_tokens[0]) > 4 || tempnum == 0 || (number - tempnum) < 1)
		{
			printf("Error: Invalid history location given\n");
			return;
		}
		else
		{
			number = number - tempnum;
			//printf("!- number: %d\n", number);
		}
	}
	else
	{
		char temp[3];
		memcpy(temp, &input_tokens[0][1], 2);
		temp[3] = '\0';

		uint8_t tempnum = atoi(temp);

		if (strlen(input_tokens[0]) > 3 || tempnum == 0 || tempnum > number)
		{
			printf("Error: Invalid history location given\n");
			return;
		}
		else
		{
			number = tempnum;
			//printf("! number: %d\n", number);
		}	
	}
	
	//printf("%s\n", history->command[number][0]);
	int i;
	for (i = 0; history.command[number][i]!= NULL; i++){
		input_tokens[i] = history.command[number][i];
	}
	input_tokens[i] = NULL;
}

bool print_history(char** parameters)
{
	for (uint8_t i = 0; i < HIST_LEN; i++)
    {
        uint8_t j = 0;
        while (history.command[i][j] != NULL)
        {
            printf("%s\n", history.command[i][j]);
            j++;
        }

    }
	return true;
}
