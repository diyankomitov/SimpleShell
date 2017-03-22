//
// Created by cxb15176 on 22/03/17.
//

#include <shell_alias.h>
#include <stdlib.h>

#define ALIAS_LEN 10

typedef struct
{
    char* name;
    char* command[HIST_LEN][INPUT_LEN/2];
} aliascontainer;

aliascontainer* aliases[ALIAS_LEN];

uint8_t count_aliases()
{
    uint8_t count = 0;

    while (aliases[count] != NULL)
        count++;

    return count;
}

