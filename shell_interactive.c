#include "shell.h"

/**
 * shell_interactive - UNIX command line interpreter
 *
 * Return: void
 */
void shell_interactive(void)
{
    char *line;
    char **args;
    int status = -1;
    char cwd[200];
    
    do {
        getcwd(cwd, sizeof(cwd));
        
        // Display prompt with bold colors
        printf("\033[1;32msimple-shell:\033[1;34m~%s$\033[0m ", cwd); /* simple-shell in bold green, cwd in bold blue */
        
        line = read_line(); /* read line from stdin */
        args = split_line(line); /* tokenize line */
        status = execute_args(args);
        
        /* avoid memory leaks */
        free(line);
        free(args);
        
        /* exit with status */
        if (status >= 0) {
            exit(status);
        }
    } while (status == -1);
}
