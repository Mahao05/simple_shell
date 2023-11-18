#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 100
#define MAX_ARGS 10

/**
 * execute_command - execute a command with arguments
 * @args: array of arguments
 */
void execute_command(char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	char input[MAX_LENGTH];
	char *args[MAX_ARGS];
	int i, num_args;

	while (1)
	{
		printf("$ ");
		fgets(input, MAX_LENGTH, stdin);

		num_args = 0
		args[num_args] = strtok(input, " \n");
		while (args[num_args] != NULL && num_args < MAX_ARGS - 1)
		{
			num_args++;
			args[num_args] = strtok(NULL, " \n");
		}
		args[num_args] = NULL;

		execute_command(args);
	}

	return (0);
}
