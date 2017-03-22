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

uint8_t count_aliases()
{
    uint8_t count = 0;

    while (aliases[count] != NULL)
        count++;

    return count;
}

void add_alias(char* alias_name, char** command)
{
    uint8_t index = count_aliases();
    aliascontainer* temp_alias = malloc(sizeof(aliascontainer));
    if (index != 10)
    {
        temp_alias->name = strdup(alias_name);
        uint8_t i = 0;
        for (; command[i] != NULL; i++)
            temp_alias->command[i] = strdup(command[i]);

        temp_alias->command[i] = NULL;

        aliases[index] = temp_alias;
    }
    else
    {
        printf("Error: The aliasaes is full!\n");
        return;
    }
}

void print_aliases()
{
    for (uint8_t i = 0; i < ALIAS_LEN && aliases[i] != NULL; i++)
    {
        printf("%s - ", aliases[i]->name);
        for (uint8_t j = 0; aliases[i]->command[j] != NULL; j++)
        {
            printf("%s ", aliases[i]->command[j]);
        }
        printf("\n");
    }
}

void get_alias(char* alias_name, char** result)
{
    for (uint8_t i = 0; i < count_aliases() && aliases[i] != NULL; i++)
        if (strcmp(aliases[i]->name, alias_name) == 0)
        {
            for (uint8_t j = 0; aliases[i]->command[j] != NULL; j++)
                result[j] = aliases[i]->command[j];

            return;
        }

    for (uint16_t i = 0; i < INPUT_LEN/2; i++)
        result[i] = NULL;
}

void remove_alias(char* alias_name)
{
    // 0 1 2 3 4 5 6 7 8 9

    for (uint8_t i = 0; i < count_aliases() && aliases[i] != NULL; i++)
    {
        if (strcmp(aliases[i]->name, alias_name) == 0)
        {
            // i cointains the index whe need remove
            printf("%d", count_aliases());
            for (uint8_t j = i+1; j < count_aliases(); j++)
                aliases[j-1] = aliases[j];


            aliases[count_aliases() - 1] = NULL;


            return;
        }
    }

}

