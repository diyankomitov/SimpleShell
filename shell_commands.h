#ifndef CS210_SEM2_SHELL_EXTERNAL_H
#define CS210_SEM2_SHELL_EXTERNAL_H

#include <stdint.h>
#include <stdbool.h>
#define COMMAND_AMMOUNT 4

typedef bool (*command)(char** parameters);

typedef struct {

    char* name;
    command callback;

} command_map;

const command_map commands[COMMAND_AMMOUNT];

void save_env();
bool exec_internal(char** token);
bool exec_external(char** tokenized_command);
bool cd(char** token);
bool exit_shell(char** parameters);
bool get_path(char** parameters);
bool set_path(char** parameters);
#endif //CS210_SEM2_SHELL_EXTERNAL_H
