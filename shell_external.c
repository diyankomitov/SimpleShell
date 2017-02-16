#include <shell_external.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_MESS_LENGTH 400

void exec_external(char** tokenized_command)
{
    __pid_t child_process_id = fork();

    if (child_process_id < 0)
        return;

    if (child_process_id == 0)
    {
        execvp(tokenized_command[0], tokenized_command);

        exit(errno);
    }
    else
    {
        signed int status;
        wait(&status);

        // http://man7.org/linux/man-pages/man3/errno.3.html
	
		char error_message[ERR_MESS_LENGTH];
		strerror_r(status, error_message, ERR_MESS_LENGTH);

        if (status == 512)
			printf("Command not found\n");
		else if (status != 0)
			printf("%s\n", error_message );

    }

}
