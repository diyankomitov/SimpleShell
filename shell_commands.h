#ifndef CS210_SEM2_SHELL_EXTERNAL_H
#define CS210_SEM2_SHELL_EXTERNAL_H

#include <stdint.h>
#include <stdbool.h>

#define COMMAND_AMOUNT 7
#define INPUT_LEN 512

typedef bool (*command)(char** parameters);

typedef struct
{
    char* name;
    command callback;

} command_map;

/*
 * Data structure containing possible input strings and the function which they link to
 */
const command_map commands[COMMAND_AMOUNT];

/*
 * Function for current path to be saved
 */
void save_env();

/*
 * Checks if input matches an internal command and if it does it calls the related function
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool exec_internal(char** token);

/*
 * Runs the input as an external command
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool exec_external(char** tokenized_command);

/*
 * Changes the current directory to the given path
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool cd(char** parameters);

/*
 * Handles exiting the shell: resets the path and saves the history and the aliases
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool exit_shell(char** parameters);

/*
 * Determines whether a new alias is to be set or the current aliases are to be printed
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool alias(char** parameters);

/*
 * Displays the current path
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool get_path(char** parameters);

/*
 * Sets the current path
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool set_path(char** parameters);
#endif //CS210_SEM2_SHELL_EXTERNAL_H
