#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <shell_input.h>

void parse(char **output, char *input)
{
    const char delimeters[8] = {'\t', '|', '<', '>', ';', '&', ' ', '\n'};

    uint8_t i;
    char* token;
    
    for (i = 0, token = strtok(input, delimeters); token != NULL; token = strtok(NULL, delimeters), i++)
    {
        output[i] = token;
    }
    
	output[i] = NULL;
}

void echo_input(char **input)
{
    for (uint8_t i = 0; input[i] != NULL; i++)
    {
        printf("'%s'\n", input[i]);
    }
}

bool is_history_command(char** command)
{
    return command[0][0] == '!';
}
