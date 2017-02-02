#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MEM_SIZE 32
#define STR_LEN 512

void read_from_console(char mem[][STR_LEN]);
void main(int argc, char * argv[]){
	int i;
	char mem[MEM_SIZE][STR_LEN];
	read_from_console(mem);
	return;	
}

void read_from_console(char mem[][STR_LEN]){

	char input[STR_LEN] = {""};
	int count = 0;
	int i = 0;
	for (i = 0; i < MEM_SIZE; i++){ 
	    strcpy(mem[i], "00000000");
	}
	while(strcmp(input,"exit\n") != 0){
		printf("> ");
		i = 0;
		char c;
		fgets(input, sizeof(input), stdin);
		printf("%s", input);
	}
}
