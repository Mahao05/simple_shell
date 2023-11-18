#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - prints all arguments it receives
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *command = NULL;
	size_t len = 0;

	while (1)
	{
		printf("$ ");
		command = NULL;
		if (getline(&command, &len, stdin) == -1)
		{
			break;
		}
		if (command[strlen(command) - 1] == '\n')
		{
			command[strlen(command) - 1] = '\0';
		}
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		printf("%s\n", command);
		free(command);
	}

	return (0);
}
