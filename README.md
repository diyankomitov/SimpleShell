# CS210 group shell project (v0.1)

developers

 * Gavin Craig
 * Gordon Clark
 * Diyan Komitov
 * Karol Groszewski
 * Bence Sebestyen 

## Building

WITH CMAKE

 0. if <project-path>/cmake-build-debug and <project-path>/build direcotires not exeist make it
 1. cd to directory <project-path>/cmake-build-debug
 2. cmake ../
 2. make

WITH GCC
    gcc -I ./ shell.c  shell_input.c shell_commands.c shell_alias.c shell_history.c -o build/cs210_sem2

the built executable can be found in <project-path>/build

