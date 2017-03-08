#ifndef SHELL_INPUT_HEADER
#define SHELL_INPUT_HEADER

#include <stdbool.h>

/*
 * Parses an input string, splits it into smaller tokens
 * and adds them to an array of char pointers
 * Parameteres:
 *		input: the input string to be parsed.
 *		output: the array of char pointers
 */
void parse(char **output, char *input);

void echo_input(char **input);

bool is_history_command(char** command);

#endif
