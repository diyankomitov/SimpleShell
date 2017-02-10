#include <string.h>
#include <stdio.h>
#include <shell_input.h>
#include <stdlib.h>
#include <shell_external.h>

#define INPUT_LEN 512

void main(int argc, char * argv[])
{
    // +1 to hold '\0' character
	char input[INPUT_LEN+1];

    // declared every loop so that it is cleared from tokens
	char* input_tokens[INPUT_LEN/2] = { NULL };
	while(1)
    {
		printf("> ");
        // +2 since fgets adds an extra '\n' char which we remove later
		fgets(input, INPUT_LEN+2, stdin);

		memset(input_tokens, 0, (INPUT_LEN/2));
		parse(input_tokens, input);

        // if Ctrl+D which gives EOF or exit input, exit
        // external shell commands should be handled before the internal ones.
        // due to override reasions
        // we have to make sure none of the external command overlaps with the kernelcommands
        // kernelcommand > internal shell command
        if (feof(stdin) || strcmp(input,"exit") == 0)
            exit(0);

        exec_external(input_tokens);
	}
}


