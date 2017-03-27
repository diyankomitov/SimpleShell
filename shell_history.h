#ifndef CS210_SEM2_SHELL_HISTORY_H
#define CS210_SEM2_SHELL_HISTORY_H

#include <stdint.h>
#include <stdbool.h>

#define HIST_LEN 20
#define HIST_LOC ".hist_list"

typedef struct
{
	bool isFull;
	uint8_t num;
	char* command[HIST_LEN][INPUT_LEN/2];
} histList;

/*
 * Loads the history of entered commands from a file, .hist_list. Will set to default values if no history is found
 */
void load_history();

/*
 * Saves the history of entered commands to a file, .hist_list
 */
void save_history();

/*
 * Adds the entered command to the history
 * Parameters:
 * Tokenised input (Array of Strings)
 */
void save_to_history(char** input_tokens);

/*
 * Retrieves and calls commands from history.
 * Command called depends on whether it is of the form
 * !n: calls command at the nth position in history
 * !!: calls the last entered command
 * !-n: calls the command at the current place in history - n
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool load_from_history(char** input_tokens);

/*
 * Displays the current contents of history in an ordered list from 1 to however items are in history (Max 20)
 * Parameters:
 * Tokenised input (Array of Strings)
 */
bool print_history(char** parameters);

#endif //CS210_SEM2_SHELL_HISTORY_H
