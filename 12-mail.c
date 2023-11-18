#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * execute_command - Executes a command in a child process
 * @command: The command to execute
 * Return: The exit status of the child process
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}

	if (pid == 0)
	{
		char *argv[2];

		argv[0] = command;
		argv[1] = NULL;

		if (execvp(argv[0], argv) == -1)
		{
			perror("Exec failed");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return WEXITSTATUS(status);
}

/**
 * execute_logical_operation - Executes a logical operation based on the return code of the previous command
 * @command: The command to execute
 * @prev_command_status: The exit status of the previous command
 * Return: The exit status of the logical operation
 */
int execute_logical_operation(char *command, int prev_command_status)
{
	char *token;
	char *saveptr;
	int status = prev_command_status;

	token = strtok_r(command, "&&", &saveptr);

	while (token != NULL)
	{
		if (status == 0)
		{
			status = execute_command(token);
		}

		token = strtok_r(NULL, "&&", &saveptr);
	}

	if (status == 0)
	{
		token = strtok_r(NULL, "||", &saveptr);

		while (token != NULL)
		{
			status = execute_command(token);
			token = strtok_r(NULL, "||", &saveptr);
		}
	}

	return status;
}

/**
 * main - Entry point of the program
 * @argc: The number of command line arguments
 * @argv: The array of command line arguments
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char **argv)
{
	char *command;
	int status;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <command>\n", argv[0]);
		return 1;
	}

	command = argv[1];

	status = execute_logical_operation(command, 0);

	if (status != 0)
	{
		fprintf(stderr, "Command failed with exit status %d\n", status);
		return 1;
	}

	return 0;
}
