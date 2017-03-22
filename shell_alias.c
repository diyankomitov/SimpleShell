//
// Created by cxb15176 on 22/03/17.
//

#include <shell_alias.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <shell_commands.h>

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

