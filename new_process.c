// //new_process.c
// #include "shell.h"

// /**
//  * new_process - create a new process
//  * @args: array of strings that contains the command and its flags
//  *
//  * Return: 1 if success, 0 otherwise.
//  */
// int new_process(char **args)
// {
//  pid_t pid;
//  int status;

// pid = fork();
//  if (pid ==  0)
//  {
//   /* child process */
//   if (execvp(args[0], args) == -1)
//   {
//    perror("error in new_process: child process");
//   }
//   exit(EXIT_FAILURE);
//  }
//  else if (pid < 0)
//  {
//   /* error forking */
//   perror("error in new_process: forking");
//  }
//  else
//  {
//   /* parent process */
//   do {
//    waitpid(pid, &status, WUNTRACED);
//   } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//  }
//  return (-1);
// }



#include "shell.h"
#include <fcntl.h>

int new_process(char **args)
{
    pid_t pid;
    int status, fd;

    pid = fork();
    if (pid == 0) {
        // Child process

        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0) {
                // Output redirection (overwrite)
                args[i] = NULL;  // Terminate args to execute the command up to '>'
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
                dup2(fd, STDOUT_FILENO);  // Redirect stdout to the file
                close(fd);
                break;
            } else if (strcmp(args[i], ">>") == 0) {
                // Output redirection (append)
                args[i] = NULL;  // Terminate args to execute the command up to '>>'
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
                dup2(fd, STDOUT_FILENO);  // Redirect stdout to the file
                close(fd);
                break;
            } else if (strcmp(args[i], "<") == 0) {
                // Input redirection
                args[i] = NULL;  // Terminate args to execute the command up to '<'
                fd = open(args[i + 1], O_RDONLY);
                if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
                dup2(fd, STDIN_FILENO);  // Redirect stdin to the file
                close(fd);
                break;
            }
        }

        // Execute command
        if (execvp(args[0], args) == -1) {
            perror("error in new_process: child process");
        }
        exit(EXIT_FAILURE);

    } else if (pid < 0) {
        // Error forking
        perror("error in new_process: forking");

    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return -1;
}
