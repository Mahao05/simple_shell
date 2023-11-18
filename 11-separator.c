#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define DELIM ";"

/* Function to execute a command */
void execute_command(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("shell");
    }
    else
    {
        /* Parent process */
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/* Function to parse commands and execute them */
void parse_commands(char *line)
{
    char *args[MAX_ARGS];
    int i = 0;

    args[i] = strtok(line, " \t\n");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    execute_command(args);
}

/* Function to read user input */
char *read_input(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("shell");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

/* Main shell loop */
void shell_loop(void)
{
    char *line;
    char *command;
  
  while (1)
    {
         printf("shell> ");
        line = read_input();

        command = strtok(line, DELIM);
        while (command != NULL)
        {
            parse_commands(command);
            command = strtok(NULL, DELIM);
        }
    }
}
/* Main function */
int main(void)
{
  shell_loop();
  return EXIT_SUCCESS;
}
