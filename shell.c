#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shell_alias.h>
#include <shell_commands.h>
#include <shell_input.h>
#include <shell_history.h>

void main(int argc, char * argv[])
{
	save_env();
	chdir(getenv("HOME"));
	load_history();
	load_aliases();
	char input[INPUT_LEN+1];
	char* input_tokens[INPUT_LEN/2] = { NULL };

	while(1)
    {
		printf("> ");
        fgets(input, INPUT_LEN+2, stdin);

        memset(input_tokens, 0, (INPUT_LEN/2));     // Clearing input_tokens

        if (feof(stdin))
            exit_shell(input_tokens);

		parse(input_tokens, input);

		if(input_tokens[0] != NULL)
		{
            bool exec_command = true;

            if(input_tokens[0][0] == '!')
			{
                exec_command = load_from_history(input_tokens);
                get_alias(input_tokens);
            }
            else
            {
                save_to_history(input_tokens);
                get_alias(input_tokens);
            }

			if (exec_command)
			{
				if (!exec_internal(input_tokens))
					exec_external(input_tokens);
			}
		}
	}
}
