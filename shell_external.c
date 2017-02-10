#include <shell_external.h>
#include <stdio.h>
#include <unistd.h>

uint8_t exec_external(char** tokenized_command)
{
    //print command name
    printf("'%s'\n", tokenized_command[0]);

    execvp(tokenized_command[0], tokenized_command);

    return 1;
}