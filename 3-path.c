#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - prints all arguments it receives
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: Always 0
 */
int main(int argc, char **argv, char **envp)
{
	int i;
	char *path = NULL;
	char *command = NULL;
	char **args = NULL;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		command = NULL;
		size_t len = 0;
		if (getline(&command, &len, stdin) == -1)
		{
			break;
		}
		if (command[strlen(command) - 1] == '\n')
		{
			command[strlen(command) - 1] = '\0';
		}
		args = malloc(sizeof(char *) * (strlen(command) + 1));
		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		args[0] = strtok(command, " ");
		for (i = 1; i < strlen(command); i++)
		{
			args[i] = strtok(NULL, " ");
		}
		args[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			path = getenv("PATH");
			args[0] = strcat("/", args[0]);
			args[0] = strcat(path, args[0]);
			if (execve(args[0], args, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
		free(args);
	}

	return (0);
}
