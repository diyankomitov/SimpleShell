#ifndef CS210_SEM2_SHELL_EXTERNAL_H
#define CS210_SEM2_SHELL_EXTERNAL_H

#include <stdint.h>
#include <stdbool.h>

#define COMMAND_AMOUNT 7
#define HIST_LEN 20
#define INPUT_LEN 512
#define HIST_LOC ".hist_list"

typedef struct {
	bool isFull;
	uint8_t num;
	char* command[HIST_LEN][INPUT_LEN/2];
} histList;

typedef bool (*command)(char** parameters);

typedef struct {

    char* name;
    command callback;

} command_map;

/*
Data structure containing possible input strings and the function which they link to
*/
const command_map commands[COMMAND_AMOUNT];

/*
Function for current path to be saved
*/
void save_env();

/*
Loads the history of entered commands from a file, .hist_list. Will set to default values if no history is found
*/
void load_history();

/*
Saves the history of entered commands to a file, .hist_list
*/
void save_history();

/*
Checks if input matches an internal command and if it does it calls the related function
Parameters:
Tokenised input (Array of Strings)
*/
bool exec_internal(char** token);

/*
Runs the input as an external command
Parameters:
Tokenised input (Array of Strings)
*/
bool exec_external(char** tokenized_command);

/*
Changes the current directory to the given path
Parameters:
Tokenised input (Array of Strings)
*/
bool cd(char** parameters);

/*
Handles exiting the shell: resets the path and saves the history and the aliases
Parameters:
Tokenised input (Array of Strings)
*/
bool exit_shell(char** parameters);

/*
Displays the current path
Parameters:
Tokenised input (Array of Strings)
*/
bool get_path(char** parameters);

/*
Sets the current path
Parameters:
Tokenised input (Array of Strings)
*/
bool set_path(char** parameters);

/*
Adds the entered command to the history
Parameters:
Tokenised input (Array of Strings)
*/
void save_to_history(char** input_tokens);

/*
Retrieves and calls commands from history. 
Command called depends on whether it is of the form 
!n: calls command at the nth position in history
!!: calls the last entered command
!-n: calls the command at the current place in history - n
Parameters:
Tokenised input (Array of Strings)
*/
bool load_from_history(char** input_tokens);

/*
Displays the current contents of history in an ordered list from 1 to however items are in history (Max 20)
Parameters:
Tokenised input (Array of Strings)
*/
bool print_history(char** parameters);

/*
Determines whether a new alias is to be set or the current aliases are to be printed
Parameters:
Tokenised input (Array of Strings)
*/
bool alias(char** parameters);
#endif //CS210_SEM2_SHELL_EXTERNAL_H
