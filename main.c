#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 100

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *argv[MAX_ARGS];
    char *token;
    int argc;

    while (1)
    {
        printf("msh> ");
        fflush(stdout);

        length = getline(&line, &capacity, stdin);

        if (length == -1)
        {
            break;
        }

        argc = 0;
        token = strtok(line, " \t\n");

        while (token != NULL && argc < MAX_ARGS - 1)
        {
            argv[argc++] = token;
            token = strtok(NULL, " \t\n");
        }

        argv[argc] = NULL;

        if (argc == 0)
        {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
        }
        else if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }

    free(line);

    printf("\nShell exited successfully.\n");

    return 0;
}