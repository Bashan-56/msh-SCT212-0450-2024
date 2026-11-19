
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
    int last_status = 0;
    int status;

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

        if (strcmp(argv[0], "exit") == 0)
        {
            break;
        }

        if (strcmp(argv[0], "help") == 0)
        {
            printf("Available commands:\n");
            printf("cd [directory] - Change directory\n");
            printf("help - Display available commands\n");
            printf("status - Display previous exit status\n");
            printf("exit - Exit the shell\n");
            last_status = 0;
            continue;
        }

        if (strcmp(argv[0], "status") == 0)
        {
            printf("Last exit status: %d\n", last_status);
            continue;
        }

        if (strcmp(argv[0], "cd") == 0)
        {
            const char *directory = (argc > 1) ? argv[1] : getenv("HOME");

            if (directory == NULL)
            {
                fprintf(stderr, "cd: HOME directory not found\n");
                last_status = 1;
            }
            else if (chdir(directory) != 0)
            {
                perror("cd");
                last_status = 1;
            }
            else
            {
                last_status = 0;
            }

            continue;
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            last_status = 1;
        }
        else if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid failed");
                last_status = 1;
            }
            else if (WIFEXITED(status))
            {
                last_status = WEXITSTATUS(status);
            }
            else if (WIFSIGNALED(status))
            {
                last_status = 128 + WTERMSIG(status);
            }
        }
    }

    free(line);

    printf("\nShell exited successfully.\n");

    return 0;
}
