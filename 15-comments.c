#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    while (1) 
    {
        char input[MAX_INPUT_SIZE];
        char *args[MAX_INPUT_SIZE / 2 + 1];
        
        printf("$ ");
        fflush(stdout);
        
        fgets(input, MAX_INPUT_SIZE, stdin);
        
        // Remove trailing newline character
        input[strcspn(input, "\n")] = 0;
        
        // Check if it's a comment
        if (input[0] == '#') 
        {
            continue; // Ignore comment, go back to the beginning of the loop
        }
        
        // Tokenize the input string
        char *token = strtok(input, " ");
        int num_args = 0;
        
        while (token != NULL) 
        {
            args[num_args] = token;
            num_args++;
            
            token = strtok(NULL, " ");
        }
        
        args[num_args] = NULL;

        // Execute the command
        pid_t pid = fork();
        
        if (pid == 0)
        {
            execvp(args[0], args);
            
            // execvp() only returns if there's an error
            perror("Error");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
