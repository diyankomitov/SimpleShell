#include <shell_external.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

uint8_t exec_external(char** tokenized_command)
{
    __pid_t child_process_id = fork();

    if (child_process_id == 0)
    {
        execvp(tokenized_command[0], tokenized_command);
    }
    else
    {
        // wait for the fork execution finish
        wait(NULL);
    }

    return 1;
}