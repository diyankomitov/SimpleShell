//
// Created by cxb15176 on 22/03/17.
//

#include <shell_alias.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <shell_commands.h>
#include <shell_input.h>

#define ALIAS_LEN 10

typedef struct
{
    char* name;
    char* command[INPUT_LEN/2];
} aliascontainer;

aliascontainer* aliases[ALIAS_LEN];

void load_alias()
{	
	FILE *ali;
	ali = fopen(ALI_LOC, "r");
	if (ali == NULL){
		printf("Alias file not found, new alias file will be created on close\n");
	}
	else {	
		char input[INPUT_LEN+1];
		char* input_tokens[INPUT_LEN/2] = { NULL };
		while(fgets(input, INPUT_LEN+2, ali)){
			memset(input_tokens, 0, (INPUT_LEN/2));
			parse(input_tokens, input);
			add_alias(input_tokens);	
		}
        fclose(ali);
	}

}


void save_alias()
{
	FILE *ali;
	ali = fopen(ALI_LOC, "w");
	int j;
	
	for (int i = 0; i < count_aliases(); i++){
		fprintf(ali, "alias %s", aliases[i]->name);
		j = 0;	
		while(aliases[i]->command[j] != NULL){
			fprintf(ali, " %s", aliases[i]->command[j]);
			j++;
		}
		fputs("\n", ali);
		
	}
	fclose(ali);
}

uint8_t count_aliases()
{
    uint8_t count = 0;

    while (aliases[count] != NULL)
        count++;

    return count;
}

bool add_alias(char** command)
{
    uint8_t index = count_aliases();
    aliascontainer* temp_alias = malloc((sizeof(aliascontainer)+1));
    if (index != 10)
    {
//        echo_input(command);
        char *alias_name = command[1];
        temp_alias->name = strdup(alias_name);
        uint8_t i = 2;
        for (; command[i] != NULL; i++)
        {
            temp_alias->command[i-2] = strdup(command[i]);
        }

        temp_alias->command[i-2] = NULL;

        for (i = 0; i < count_aliases() && aliases[i] != NULL; i++)
        {
            if (strcmp(aliases[i]->name, temp_alias->name) == 0)
            {
                aliases[i] = temp_alias;
                printf("%s: alias changed\n", temp_alias->name);
                return true;
            }
        }

        aliases[index] = temp_alias;

        return true;
    }
    else
        return false;
}

void print_aliases()
{
    uint8_t i = 0;
    for (; i < ALIAS_LEN && aliases[i] != NULL; i++)
    {
        printf("%s - ", aliases[i]->name);
        for (uint8_t j = 0; aliases[i]->command[j] != NULL; j++)
        {
            printf("%s ", aliases[i]->command[j]);
        }
        printf("\n");
    }

    if (i == 0)
        printf("Warning: no aliases yet!\n");
}

bool get_alias(char** command)
{
    for (uint8_t i = 0; i < count_aliases() && aliases[i] != NULL; i++)
        if (strcmp(aliases[i]->name, command[0]) == 0)
        {
            char** temp = malloc(sizeof(command[0])*INPUT_LEN/2);
            uint8_t j = 0;
            for(; command[j] != NULL; j++)
                temp[j] = command[j];

            temp[j] = NULL;

            j = 0;
            for (; aliases[i]->command[j] != NULL; j++)
                command[j] = aliases[i]->command[j];

            uint8_t k = 1;
            for(; temp[k] != NULL; k++)
                command[j+(k-1)] = temp[k];

            free(temp);
            command[j+(k-1)] = NULL;

            return true;
        }

    return false;
}

bool remove_alias(char** command)
{
    // 0 1 2 3 4 5 6 7 8 9
    if (command[1] == NULL)
    {
        printf("Error: Unalias requires parameters\n");
        return false;
    }

    for (uint8_t i = 0; i < count_aliases() && aliases[i] != NULL; i++)
    {
        if (strcmp(aliases[i]->name, command[1]) == 0)
        {
            for (uint8_t j = i+1; j < count_aliases(); j++)
                aliases[j-1] = aliases[j];

            aliases[count_aliases() - 1] = NULL;

            return true;
        }
    }

    printf("%s: this alias does not exist\n", command[1]);
    return false;

}

