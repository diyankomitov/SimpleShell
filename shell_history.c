#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shell_commands.h>
#include <shell_alias.h>
#include <shell_input.h>
#include <shell_history.h>

histList history;

void save_history()
{
	FILE *hist = fopen(HIST_LOC, "w");
	
	fprintf(hist, "%u\n", history.num);
	fprintf(hist, "%d\n", history.isFull);

	for(uint8_t i = 0; history.command[i][0] != NULL && i < HIST_LEN; i++)
	{
		for(uint8_t j = 0; history.command[i][j] != NULL; j++)
			fprintf(hist, "%s ", history.command[i][j]);

		fputs("\n", hist);
	}
	fclose(hist);
}

void load_history()
{
	FILE *hist = fopen(HIST_LOC, "r");
	if (hist == NULL)
	{
		printf("History file not found, new history file will be created on close\n");
		history.num = 0;
		history.isFull = false;
	}
	else
	{
		char hist_num[3];
		fgets(hist_num, sizeof(hist_num), hist);
		
		char isFull[3];
		fgets(isFull, sizeof(isFull), hist);
		history.isFull = isFull[0] == '1' ? true : false;

		char input[INPUT_LEN+1];
		char* input_tokens[INPUT_LEN/2] = { NULL };

		while(fgets(input, INPUT_LEN+2, hist))
		{
			memset(input_tokens, 0, (INPUT_LEN/2));
			parse(input_tokens, input);
			save_to_history(input_tokens);
		}
		if (history.isFull)
			history.num = atoi(hist_num);
		
		fclose(hist);
	}	
}

void save_to_history(char** input_tokens){
	uint8_t i;
	for (i = 0; input_tokens[i]!= NULL; i++)
        history.command[history.num][i] = strdup(input_tokens[i]);
	
	history.command[history.num][i] = NULL;
	history.num = history.num = (history.num + 1)% HIST_LEN;

	if(history.num == 0)
		history.isFull = true;
} 

bool load_from_history(char* input_tokens[])
{
	if (history.command[0][0] == NULL)
	{
		printf("Error: History is empty\n");
		return false;
	}
	else
	{
		if(input_tokens[1] != NULL)
		{
			printf("Error: invocation from history can't have any arguments\n");
			return false;
		}

		int8_t number = history.num-1;
	
		if (!(strcmp(input_tokens[0], "!!") == 0 || strcmp(input_tokens[0], "!-0") == 0))
		{
			if (input_tokens[0][1] == '-')
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
							number = HIST_LEN + number;
					}
					else
					{
						if(tempnum <= number)
						number = number - tempnum;

						else
						{
							printf("Error: invalid history location given\n");
							return false;
						}
					}
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
					number = history.isFull ? (number + tempnum) % HIST_LEN : tempnum-1;
			}
		}

		uint8_t i;
		for (i = 0; history.command[number][i]!= NULL; i++)
			input_tokens[i] = history.command[number][i];

		input_tokens[i] = NULL;
		return true;
	}
}

bool print_history(char** parameters)
{
	if (parameters[1] != NULL)
	{
		printf("Error: history cannot take any arguments\n");
		return false;
	}
	else {
		uint8_t count = 0;
		uint8_t i = history.num;
		uint8_t j;

		if(history.isFull){
			for(; count < HIST_LEN; count++)
			{		
				printf("%d. ", count+1);
			
				for(j = 0; history.command[i][j] != NULL; j++)
					printf("%s ", history.command[i][j]);

				printf("\n");

				i = (i+1) % HIST_LEN;
			}
		}
		else{
			for(; count<history.num; count++)
			{
				printf("%d. ", count+1);

				for(j = 0; history.command[count][j] != NULL; j++)
					printf("%s ", history.command[count][j]);

				printf("\n");
			}
		}
		return true;
	}	
}
