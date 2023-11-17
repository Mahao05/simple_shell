#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char *buffer;
	size_t bufsize = 1024;

	buffer = malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (getline(&buffer, &bufsize, stdin) != -1)
	{
		printf("%s", buffer);
	}

	free(buffer);
	return (0);
}
