#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Failed");
		exit(-1);
	}
	else if (pid==0) {
		execlp("output", "output");
		printf("\n");
		}
	else {
			wait(NULL);
			printf("done\n");
			exit(0);
		}
}

