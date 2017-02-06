#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <shell_input.h>
#define INPUT_LEN 512

void main(int argc, char * argv[])
{
	char input[INPUT_LEN+1]; 		// +1 to hold '\0' character
	while(1){
		printf("> ");
		fgets(input, INPUT_LEN+2, stdin);		// +2 since fgets adds an extra '\n' char which we remove later

		
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

