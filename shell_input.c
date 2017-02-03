#include <shell_input.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 512

void read_from_console() {
	char input[STR_LEN+1]; 		// +1 to hold '\0' character
	while(1){
		printf("> ");
		fgets(input, STR_LEN+2, stdin);		// +2 since fgets adds an extra '\n' char which we remove later

		
		if (feof(stdin)) {		// if Ctrl+D which gives EOF, exit
				printf("\n");
				return;
		}
		else if (input[strlen(input)-1] != '\n')		// if input is too long it won't end in a '\n'
		{
			flush_stdin();
			printf("> Error: input is too long\n");
		}
		else {
			input[strlen(input)-1] = '\0';		// otherwise replace '\n' with '\0'

			if (strcmp(input,"exit") == 0) {
				return;
			}

			parse(input);
		}
	}
}

void parse(char *input){
	char *token = strtok(input, " ");		// currently only splits on space
	while (token != NULL)
	{
		printf("'%s'\n", token);

		token = strtok(NULL, " ");
	}
}

void flush_stdin() {
	int ch;
	while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
		//this will read and remove one character at a time from stdin until it reaches an EOF or a new line
}
