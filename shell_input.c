#include <shell_input.h>
#include <stdio.h>
#include <string.h>

void parse(char **output, char *input)
{
    const char delimeters[8] = {'\t', '|', '<', '>', ';', '&', ' ', '\n'};
	char *token = strtok(input, delimeters);       // splits first token
    
    int i= 0;
    while (token != NULL)
    {
        output[i] = token;          // while there are tokens, add to output
        i++;

        token = strtok(NULL, delimeters);       // keep splitting
    }
}

void echo_input(char **input)
{
	int i = 0;
		while(input[i] != NULL)
		{
			printf("'%s'\n", input[i]);
			i++;
		}
}
