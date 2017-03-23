#include <shell_commands.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <shell_commands.h>
#include <shell_alias.h>
#include <shell_input.h>

char* env_save;
histList history;

const command_map commands[COMMAND_AMMOUNT] =
{
	{.name = "getpath", .callback = &get_path}
	,{.name = "setpath", .callback = &set_path}
	,{.name = "cd", .callback = &cd}
	,{.name = "exit", .callback = &exit_shell}
	,{.name = "history", .callback = &print_history}
	,{.name = "alias", .callback = &alias}
	,{.name = "unalias", .callback = &remove_alias}

};

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
		{
			if (!add_alias(parameters))
				printf("Error: alias limit reached!\n");
		}
		else
		{
			printf("Error: command not specified for the alias\n");
		}

		}

}



void save_env()
{
	env_save = getenv("PATH");
}

void load_history()
{
	FILE *hist;
	hist = fopen(HIST_LOC, "r");
	if (hist == NULL){
		printf("History file not found, new history file will be created on close\n");
		history.num = 0;
		history.isFull = false;
	}
	else{
		char flush[2];
		char hist_num[3];
		fgets(hist_num, sizeof(hist_num), hist);
		
		char isFull[2];
		fgets(isFull, sizeof(isFull), hist);
		history.isFull = isFull[0] == '1'? true: false;
		
		int i = 0;
		int j;
		char input[INPUT_LEN+1];
		char* input_tokens[INPUT_LEN/2] = { NULL };
		fgets(flush, sizeof(flush), hist);
		while(fgets(input, INPUT_LEN+2, hist)){
			memset(input_tokens, 0, (INPUT_LEN/2));
			parse(input_tokens, input);
			save_to_history(input_tokens);
			
		}
		if (history.isFull){
			history.num = atoi(hist_num);
		}
		
		fclose(hist);
	}	
}
	



void save_history(){
	
	FILE *hist;
	hist = fopen(HIST_LOC, "w");
	
	fprintf(hist, "%u\n", history.num);
	int isFull = history.isFull ? 1 : 0;
	fprintf(hist, "%d\n", isFull);
		int i = 0;
		int j;
		while(history.command[i][0] != NULL && i < HIST_LEN){
			
			j = 0;	
			while(history.command[i][j] != NULL){
				fprintf(hist, "%s ", history.command[i][j]);
				j++;
			}
			fputs("\n", hist);
			i++;
	}
	fclose(hist);
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
	chdir(getenv("HOME"));
	save_history();
	save_alias();
	setenv("PATH", env_save, 1);
	printf("%s\n", getenv("PATH"));
	exit(0);

	return true;
}

void save_to_history(char** input_tokens){
	int i;
	for (i = 0; input_tokens[i]!= NULL; i++){
		history.command[history.num][i] = strdup(input_tokens[i]);
	}
	
	history.command[history.num][i] = NULL;
	history.num = history.num = (history.num + 1)% HIST_LEN;
	if(history.num == 0)
	{
		history.isFull = true;
	}
} 

bool load_from_history(char* input_tokens[])
{
	if (history.command[0][0] == NULL){
		printf("Error: History is empty\n");
		return false;
	}
	else{
		if(input_tokens[1] != NULL)
		{
			printf("Error: invocation from history can't have any arguments\n");
			return false;
		}

		int8_t number = history.num-1;
	
		if (strcmp(input_tokens[0], "!!") == 0 || strcmp(input_tokens[0], "!-0") == 0)
		{
			number = history.num-1;
		}
		else if (input_tokens[0][1] == '-')
		{
			char temp[3];
			memcpy(temp, &input_tokens[0][2], 2);
			temp[3] = '\0';

			uint8_t tempnum = atoi(temp);

			if (strlen(input_tokens[0]) > 4 || tempnum == 0 || HIST_LEN - tempnum <= 0)
			{
				printf("Error: Invalid history location given\n");
				return false;
			}
			else
			{
				if(history.isFull)
				{
					number = number  - tempnum;

					if(number < 0)
					{
						number = HIST_LEN + number;
					}

				}
				else
				{
					if(tempnum<=number){
					number = number - tempnum;
					}
					else{
						printf("Error: invalid history location given\n");
						return false;
					}
				}
				//printf("!- number: %d\n", number);
			}
		}
		else
		{
			char temp[3];
			memcpy(temp, &input_tokens[0][1], 2);
			temp[3] = '\0';

			uint8_t tempnum = atoi(temp);

			if (strlen(input_tokens[0]) > 3 || tempnum == 0 || tempnum > HIST_LEN || (history.isFull == false && tempnum > number+1))
			{
				printf("Error: Invalid history location given\n");
				return false;
			}
			else
				number = (history.isFull)? (number + tempnum) % HIST_LEN : tempnum-1;
		}
	
	
		int i;
		for (i = 0; history.command[number][i]!= NULL; i++){
			input_tokens[i] = history.command[number][i];
		}
		input_tokens[i] = NULL;
		return true;
		
	}
}

bool print_history(char** parameters)
{
	if (parameters[1] == NULL){
		uint8_t i = history.num;
		uint8_t count = 0;
		uint8_t j = 0;
		if(history.isFull){
			while(count < HIST_LEN)
			{		
				printf("%d. ", count+1);
			
			
				while (history.command[i][j] != NULL)
				{
					printf("%s ", history.command[i][j]);
					j++;
				}
				printf("\n");
				i = (i+1)%HIST_LEN;
				count++;
				j = 0;
			}
		}
		else{
			for(count = 0; count<history.num; count++){
				printf("%d. ", count+1);
				while (history.command[count][j] != NULL)
				{
					printf("%s ", history.command[count][j]);
					j++;
				}
				printf("\n");
				j =0;
			}
		}
		return true;
	}
	else {
		printf("Error: history cannot take any arguments\n");
		return false;
	}	
}
