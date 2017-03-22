//
// Created by cxb15176 on 22/03/17.
//

#ifndef CS210_SEM2_SHELL_ALIAS_H
#define CS210_SEM2_SHELL_ALIAS_H

#include <shell_commands.h>
#include <stdint.h>

uint8_t count_aliases();
void print_aliases();
void remove_alias(char* alias_name);
void add_alias(char* alias_name, char** command);
char** get_alias(char* alias_name);

#endif //CS210_SEM2_SHELL_ALIAS_H
