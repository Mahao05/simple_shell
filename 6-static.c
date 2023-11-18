#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * _getline - reads an entire line from stream
 * @lineptr: pointer to the buffer containing the line read
 * @n: size of the buffer
 * @stream: input stream
 *
 * Return: number of characters read, 0 on failure
 */

char *custom_getline() 
{
	static char buffer[BUFFER_SIZE];
	static int position = 0;
	static int bytesRead = 0;

	char *line = NULL;
	int newlineFound = 0;

	while (!newlineFound) 
	{
		if (position == bytesRead)
		{
			position = 0;
			bytesRead = read(0, buffer, BUFFER_SIZE);
		}
		if (bytesRead <= 0) 
		{
			break;
		}
	}
	
	while (position < bytesRead)
	{
		if (buffer[position] == '\n')
		{
			newlineFound = 1;
			break;
		}
		position++;
	}

	if (line == NULL) 
	{
		line = strdup(buffer);
        } 
	else 
	{
		char *temp = realloc(line, strlen(line) + position + 1);
		if (temp == NULL) 
		{
			free(line);
			return NULL;
		}
		line = temp;
		strncat(line, buffer, position);
	}

	return line;
}
