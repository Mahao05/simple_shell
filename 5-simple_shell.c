#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints all arguments it receives
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 *
 * Return: Always 0
 */
int main() 
{
	extern char **environ;
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}

	return 0;
}
