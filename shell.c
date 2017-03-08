#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>
#include <shell_commands.h>
#include <unistd.h>
#include <stdbool.h>

#define INPUT_LEN 512

void main(int argc, char * argv[])
{
	save_env();
	chdir(getenv("HOME"));	

	char input[INPUT_LEN+1];	
	char* input_tokens[INPUT_LEN/2] = { NULL };

	while(1)
    {
		printf("> ");
 
		fgets(input, INPUT_LEN+2, stdin);

		memset(input_tokens, 0, (INPUT_LEN/2));
		
		parse(input_tokens, input);

		bool isSuccess = exec_internal(input_tokens);

        if (!isSuccess)
            exec_external(input_tokens);
	}
}