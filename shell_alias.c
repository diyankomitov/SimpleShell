//
// Created by cxb15176 on 22/03/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shell_alias.h>
#include <shell_commands.h>
#include <shell_input.h>

aliascontainer* aliases[ALIAS_LEN];

void load_aliases()
{	
	FILE *aliasfile = fopen(ALIAS_LOC, "r");
	if (aliasfile == NULL)
    {
		printf("Error: Alias file not found, new alias file will be created on exit\n");
	}
	else
    {
		char input[INPUT_LEN+1];
		char* input_tokens[INPUT_LEN/2] = { NULL };

		while(fgets(input, INPUT_LEN+2, aliasfile))
        {
			memset(input_tokens, 0, (INPUT_LEN/2));
			parse(input_tokens, input);
			add_alias(input_tokens);
		}
        fclose(aliasfile);
	}
}

void save_aliases()
{
	FILE *aliasfile = fopen(ALIAS_LOC, "w");

    uint8_t j;
	for (uint8_t i = 0; i < count_aliases(); i++)
    {
		fprintf(aliasfile, "alias %s", aliases[i]->name);
		j = 0;	
		while(aliases[i]->command[j] != NULL)
        {
			fprintf(aliasfile, " %s", aliases[i]->command[j]);
			j++;
		}
		fputs("\n", aliasfile);
	}
	fclose(aliasfile);
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
    char* temp[INPUT_LEN/2] = { NULL };
    temp[0] = command[1];

    if (index == ALIAS_LEN && !get_alias(temp))
    {
        printf("Error: alias limit reached! Alias not added\n");
        return false;
    }

    if (is_creates_alias_cycle(command))
    {
        printf("Error: alias would create a cycle! Alias not added\n");
        return false;
    }

    aliascontainer* new_alias = malloc((sizeof(aliascontainer)+1));
    char *alias_name = command[1];
    new_alias->name = strdup(alias_name);

    uint8_t i = 2;
    for (; command[i] != NULL; i++)
        new_alias->command[i-2] = strdup(command[i]);

    new_alias->command[i-2] = NULL;

    for (i = 0; i < count_aliases() && aliases[i] != NULL; i++)
    {
        if (strcmp(aliases[i]->name, new_alias->name) == 0)
        {
            aliases[i] = new_alias;
            printf("%s: alias changed\n", new_alias->name);
            return true;
        }
    }

    aliases[index] = new_alias;
    return true;
}

void print_aliases()
{
    uint8_t i = 0;
    for (; i < ALIAS_LEN && aliases[i] != NULL; i++)
    {
        printf("%s - ", aliases[i]->name);

        for (uint8_t j = 0; aliases[i]->command[j] != NULL; j++)
            printf("%s ", aliases[i]->command[j]);

        printf("\n");
    }

    if (i == 0)
        printf("Warning: no aliases yet!\n");
}

bool get_alias(char** command)
{
    for (uint8_t i = 0; i < count_aliases() && aliases[i] != NULL; i++)
    {
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

            get_alias(command);
            return true;
        }
    }
    return false;
}

bool remove_alias(char** command)
{
    if (command[1] == NULL)
    {
        printf("Error: unalias requires parameters\n");
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

bool is_creates_alias_cycle(char** command)
{
    bool is_cycel = false;

    if (strcmp(command[1], command[2]) == 0)
        is_cycel = true;

    char* temp[INPUT_LEN/2] = { NULL };
    char* temp2[INPUT_LEN/2] = { NULL };
    temp[0] = command[2];

    get_alias(temp);

    if ((strcmp(temp[0], command[1]) == 0))
        is_cycel = true;

    temp[0] = command[1];
    temp2[0] = command[2];


    if (get_alias(temp) == true && get_alias(temp2) == true)
        is_cycel = true;

    return is_cycel;
}

