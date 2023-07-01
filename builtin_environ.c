#include "myshell.h"
/**
 * builtin_environment - show shell environment
 * @data: struct for program data
 * By Afua
 * Return: 0 on success, other if declared
 */
int builtin_environment(data_of_program *data)
{
	int x;
	char names[50] = {'\0'}, *var_dup = NULL;

	if (data->tokens[1] == NULL)
		print_environment(data);
	else
	{
		for (x = 0; data->tokens[1][x]; x++)
		{
			if (data->tokens[1][x] == '=')
			{
				var_dup = str_duplicate(environment_get_key(names, data));
				if (var_dup != NULL)
					environment_set_key(names, data->tokens[1] + x + 1, data);
				print_environment(data);
				if (environment_get_key(names, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					environment_set_key(names, var_dup, data);
					free(var_dup);
				}
				return (0);
			}
			names[x] = data->tokens[1][x];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}
/**
 * builtin_set_environment - set env
 * @data: struct for program data
 * Return: 0 on success, other if declared
 */
int builtin_set_environment(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	environment_set_key(data->tokens[1], data->tokens[2], data);
	return (0);
}
/**
 * builtin_unset_environment - unset env
 * @data: struct for program data
 * By Afua
 * Return: 0 on success, other if declared
 */
int builtin_unset_environment(data_of_program *data)
{
	if (data->tokens[1] == NULL)
	{
		return (0);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	environment_remove_key(data->tokens[1], data);
	return (0);
}
