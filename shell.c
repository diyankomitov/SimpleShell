#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>

#define INPUT_LEN 512

void main(int argc, char * argv[])
{
	char input[INPUT_LEN+1]; 		// +1 to hold '\0' character

	char* tokens[INPUT_LEN/2] = { NULL };		// declared every loop so that it is cleared from tokens
	while(1){
		printf("> ");
		fgets(input, INPUT_LEN+2, stdin);		// +2 since fgets adds an extra '\n' char which we remove later

		memset(tokens, 0, (INPUT_LEN/2));
		parse(tokens, input);

//		echo_input(tokens);			// test, remove later

		if (feof(stdin) || strcmp(input,"exit") == 0) {		// if Ctrl+D which gives EOF or exit input, exit
            exit(0);
		}	
	}
}


