#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 512

void read_from_console();
void parse(char *input);

void main(int argc, char * argv[]){
	read_from_console();
	return;	
}

/*
 * Reads user input from the console
 */
void read_from_console(){
	char input[STR_LEN] = {""};
	while(1){
		printf("> ");
		fgets(input, sizeof(input), stdin);
		input[strlen(input)-1] = '\0';

		parse(input);

		if (strcmp(input,"exit") == 0){
			return;
		}
		else if (feof(stdin)) {
			printf("\n");
			return;
		}
	}
}

/*
 * Parses an input string, splits it
 * into smaller tokens and prints them out.
 * Parameteres:
 *		input: the input string to be parsed.
 */
void parse(char *input){
	char *token = strtok(input, " ");
	while (token != NULL)
	{
		printf("'%s'\n", token);

		token = strtok(NULL, " ");
	}
}