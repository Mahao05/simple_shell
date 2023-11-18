#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/*
 * function : Display a prompt and wait for the user to type a command.
 *
 * The prompt is displayed again each time a command has been executed.
 * The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
 *
 * Return : If an executable cannot be found, print an error message and display the prompt again.
 */
 
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	ssize_t characters;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (1)
	{
		printf("$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
		{
            		break;
		}
		if (strcmp(buffer, "exit\n") == 0)
		{
			break;
		}
		printf("%s", buffer);
	}
	free(buffer);
	return 0;
}
