#ifndef SHELL_INPUT_HEADER
#define SHELL_INPUT_HEADER


/*
 * Parses an input string, splits it
 * into smaller tokens and prints them out.
 * Parameteres:
 *		input: the input string to be parsed.
 */
void parse(char *input);

/*
 * Clears stdin
 */
void flush_stdin();

#endif
