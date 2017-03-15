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
	histList history;
	history.num = 0;
	char input[INPUT_LEN+1];	
	char* input_tokens[INPUT_LEN/2] = { NULL };

	while(1)
    {
		printf("> ");
 
		fgets(input, INPUT_LEN+2, stdin);

		memset(input_tokens, 0, (INPUT_LEN/2));
		
		parse(input_tokens, input);
		
		if(input_tokens[0][0] != '!'){
			printf("presave");
			save_history(input_tokens, &history);
			printf("save");
		}
		else {
			load_history(input_tokens, &history);
			//printf("%s\n", input_tokens[0]);
		}
		bool isSuccess = exec_internal(input_tokens);
        if (!isSuccess)
            exec_external(input_tokens);
	}
}
