#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>
#include <shell_external.h>
#include <unistd.h>
#define INPUT_LEN 512

void main(int argc, char * argv[])
{
	char input[INPUT_LEN+1];
	save_env();
	char* input_tokens[INPUT_LEN/2] = { NULL };
	char* env_home = getenv("HOME");
	setenv("PATH", env_home, 0);
	chdir(env_home);	
	while(1)
    {
		printf("> ");
    
		fgets(input, INPUT_LEN+2, stdin);

		memset(input_tokens, 0, (INPUT_LEN/2));
		parse(input_tokens, input);

        
        
		exec_list(input_tokens);


	}
}


