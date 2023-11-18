#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * setenv - initialize a new environment variable, or modify an existing one
 * @var: the name of the variable
 * @value: the value of the variable
 * Return: 0 on success, -1 on failure
 */
int setenv(const char *var, const char *value)
{
    char *env_var;

    if (var == NULL || value == NULL || strchr(var, '=') != NULL)
    {
        fprintf(stderr, "Invalid arguments\n");
        return (-1);
    }

    env_var = malloc(strlen(var) + strlen(value) + 2);
    if (env_var == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return (-1);
    }

    sprintf(env_var, "%s=%s", var, value);
    if (putenv(env_var) != 0)
    {
        fprintf(stderr, "Environment variable error\n");
        free(env_var);
        return (-1);
    }

    return (0);
}

/**
 * unsetenv - remove an environment variable
 * @var: the name of the variable
 * Return: 0 on success, -1 on failure
 */
int unsetenv(const char *var)
{
    if (var == NULL || strchr(var, '=') != NULL)
    {
        fprintf(stderr, "Invalid arguments\n");
        return (-1);
    }

    if (putenv(var) != 0)
    {
        fprintf(stderr, "Environment variable error\n");
        return (-1);
    }

    return (0);
}
