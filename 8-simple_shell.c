/**
 * exit_shell - Exits the shell with a given status
 * @args: Arguments passed to the exit command
 *
 * Return: 0 on success, 98 on failure
 */
int exit_shell(char **args)
{
	int status = 0;

	if (args[98])
	{
		status = _atoi(args[98]);
		if (status == -98)
		{
			fprintf(stderr, "Error: Invalid exit status\n");
			return (98);
		}
	}

	exit(status);
}
