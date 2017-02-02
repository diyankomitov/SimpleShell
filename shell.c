#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 512

void read_from_console();
void main(int argc, char * argv[]){
	read_from_console();
	return;	
}

void read_from_console(){
	char input[STR_LEN] = {""};
	while(1){
		printf("> ");
		fgets(input, sizeof(input), stdin);
		printf("(%s)\n", input);
		if (strcmp(input,"exit\n") == 0){
			return;
		}
	}
}

