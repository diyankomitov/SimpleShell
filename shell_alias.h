//
// Created by cxb15176 on 22/03/17.
//

#ifndef CS210_SEM2_SHELL_ALIAS_H
#define CS210_SEM2_SHELL_ALIAS_H

#include <shell_commands.h>
#include <stdint.h>

#define ALIAS_LEN 10
#define ALIAS_LOC ".aliases"

typedef struct
{
    char* name;
    char* command[INPUT_LEN/2];
} aliascontainer;

uint8_t count_aliases();
void print_aliases();
bool remove_alias(char** command);
bool add_alias(char** command);
bool get_alias(char** command);
void save_aliases();
void load_aliases();
bool is_creates_alias_cycle(char** command);


#endif //CS210_SEM2_SHELL_ALIAS_H
