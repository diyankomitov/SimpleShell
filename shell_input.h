#ifndef SHELL_INPUT_HEADER
#define SHELL_INPUT_HEADER

#include <stdbool.h>
#include <stdint.h>

 
/*
 * Function takes input string and tokenises it into individual segments based on certain delimeters. 
 * Parameters:
 * String Input (String)
 * Tokenised Output (Array of Strings)
 */
void parse(char **output, char *input);

/*
 * Function takes in tokenised input and displays it separated out
 * Parameters:
 * Tokenised input (Array of Strings)
 */
void echo_input(char **input);

/*
 * Function takes in an tokenised input strings and determines whether or not they are a history command
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool is_history_command(char** command);

#endif
