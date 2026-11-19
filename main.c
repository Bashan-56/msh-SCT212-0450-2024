
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

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

    signal(SIGINT, SIG_IGN);

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

        int background = 0;
        char *input_file = NULL;
        char *output_file = NULL;

        if (strcmp(argv[argc - 1], "&") == 0)
        {
            background = 1;
            argv[--argc] = NULL;
        }

        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "<") == 0 && i + 1 < argc)
            {
                input_file = argv[i + 1];

                for (int j = i; j + 2 <= argc; j++)
                {
                    argv[j] = argv[j + 2];
                }

                argc -= 2;
                i--;
            }
            else if (strcmp(argv[i], ">") == 0 && i + 1 < argc)
            {
                output_file = argv[i + 1];

                for (int j = i; j + 2 <= argc; j++)
                {
                    argv[j] = argv[j + 2];
                }

                argc -= 2;
                i--;
            }
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
            last_status = 1;
        }
        else if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);

            if (input_file != NULL)
            {
                int fd = open(input_file, O_RDONLY);

                if (fd < 0)
                {
                    perror("input redirection");
                    exit(EXIT_FAILURE);
                }

                dup2(fd, STDIN_FILENO);
                close(fd);
            }

            if (output_file != NULL)
            {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (fd < 0)
                {
                    perror("output redirection");
                    exit(EXIT_FAILURE);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execvp(argv[0], argv);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        else if (background)
        {
            printf("Started background process with PID %d\n", pid);
            last_status = 0;
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
