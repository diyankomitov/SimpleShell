#include <shell_input.h>
#include <stdio.h>
#include <string.h>

void echo_input(char *input)
{
    while (input != NULL)
    {
        printf("'%s'\n", input);

        input = strtok(NULL, " ");
    }

}

void parse(char *input){

	char *token = strtok(input, " ");		// currently only splits on space

	echo_input(token);

}

void flush_stdin() {
	int ch;
	while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
		//this will read and remove one character at a time from stdin until it reaches an EOF or a new line
}
