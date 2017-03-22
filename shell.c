#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>
#include <shell_commands.h>
#include <unistd.h>
#include <stdbool.h>


void main(int argc, char * argv[])
{
	save_env();
	chdir(getenv("HOME"));
	load_history();
	char input[INPUT_LEN+1];	
	char* input_tokens[INPUT_LEN/2] = { NULL };
	
	while(1)
    {
		printf("> ");
 
		fgets(input, INPUT_LEN+2, stdin);

		memset(input_tokens, 0, (INPUT_LEN/2));
		
		parse(input_tokens, input);
		bool run_hist = true;
		if(input_tokens[0] == NULL) {
		}
		else if(input_tokens[0][0] != '!'){
			//printf("presave\n");
			save_to_history(input_tokens);
			//printf("save\n");
		}
		else {
			run_hist = load_from_history(input_tokens);
			//printf("%s\n", input_tokens[0]);
		}
		if (run_hist){
			bool isSuccess = exec_internal(input_tokens);
        	if (!isSuccess)
            	exec_external(input_tokens);
		}
	}
}
