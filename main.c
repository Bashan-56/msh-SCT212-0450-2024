#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

        printf("Arguments received:\n");

        for (int i = 0; i < argc; i++)
        {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
    }

    free(line);

    printf("\nShell exited successfully.\n");

    return 0;
}