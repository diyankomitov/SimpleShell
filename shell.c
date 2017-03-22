#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>
#include <shell_commands.h>
#include <unistd.h>
#include <stdbool.h>
#include <shell_alias.h>


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
		if(input_tokens[0] != NULL)
		{
			if(input_tokens[0][0] != '!')
			{
				save_to_history(input_tokens);
				get_alias(input_tokens);
			}

			if(input_tokens[0][0] == '!')
				run_hist = load_from_history(input_tokens);


			if (run_hist || input_tokens[0][0] != '!')
			{
				bool isSuccess = exec_internal(input_tokens);
				if (!isSuccess)
					exec_external(input_tokens);
			}
		}
	}
}
