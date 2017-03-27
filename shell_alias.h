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

/*
 * Returns the number of aliases that are currently stored
 */
uint8_t count_aliases();

/*
 * Function that prints the currently stored aliases
 */
void print_aliases();

/*
 * Function that remove's the given alias from the stored aliases
 * Parameters:
 * Tokenised input (Array of Strings)
*/
bool remove_alias(char** command);

/*
 * Function that adds new aliases, given a name for the alias and the function that it will perform
 * Parameters:
 * Tokenised input (Array of Strings)
*/
bool add_alias(char** command);

/*
 * Function that takes user input and checks wether it contains an alias and if it does it will pass out the command the alias refers to
 * Parameters:
 * Tokenised input (Array of Strings)
*/
bool get_alias(char** command);

/*
 * Saves currently stored aliases to a file, .aliases
 */
void save_aliases();

/*
 * Loads aliases from a file, .aliases
 */
void load_aliases();

/*
 * Function that checks if the given alias will create an infinite loop if it were to be called unchecked
 * Parameters:
 * Tokenised input (Array of Strings)
*/
bool is_creates_alias_cycle(char** command);


#endif //CS210_SEM2_SHELL_ALIAS_H
