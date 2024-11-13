#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int own_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return -1;
}

int own_env(char **args) {
    (void)args;
    extern char **environ;
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
    return -1;
}

int own_help(char **args) {
    (void)args;
    printf("Simple Shell - Supported commands:\n");
    printf("cd [dir] - change directory to 'dir'\n");
    printf("env - display environment variables\n");
    printf("help - display this help message\n");
    printf("exit - exit the shell\n");
    return -1;
}

int own_exit(char **args) {
  (void)args;
    return 0;  // Return 0 to indicate the shell should exit
}
