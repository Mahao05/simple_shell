#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_LEN 128
#define MAX_ARGS 10

int main() 
{
	char cmd[MAX_CMD_LEN];
	char *args[MAX_ARGS];
	pid_t pid;
	int status;

	while (1) 
	{
		printf("$ ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL) 
		{
			printf("\n");
			exit(0);
		}

		if (cmd[strlen(cmd) - 1] == '\n') 
		{
			cmd[strlen(cmd) - 1] = '\0';
		}

		args[0] = cmd;
		args[1] = NULL;

		pid = fork();
		if (pid < 0) 
		{
			perror("Fork failed");
			exit(1);
		}

		if (pid == 0) 
		{
			execvp(args[0], args);
			perror("Execution failed");
			exit(1);
		} 
		else 
		{
			wait(&status);
		}
	}

	return 0;
}
