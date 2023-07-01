#include "myshell.h"
/**
 * execution - execute command
 * By AFua
 * @data: struct for program data
 * Return: 0 on success, -1 on failure
 */
int execution(data_of_program *data)
{
	int r_value = 0, stat;
	pid_t pid;

	r_value = list_of_builtins(data);
	if (r_value != -1)
		return (r_value);

	r_value = finding_program(data);
	if (r_value)
	{
		return (r_value);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			r_value = execve(data->tokens[0], data->tokens, data->env);
			if (r_value == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}
