#include "myshell.h"
/**
 * environment_get_key - get environment variable
 * By Afua
 * @key: environment variable
 * @data: struct of program data
 * Return: pointer to variable or NULL
 */
char *environment_get_key(char *key, data_of_program *data)
{
	int x, length_of_key = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);
	length_of_key = str_length(key);
	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], length_of_key) && data->
				env[x][length_of_key] == '=')
		{
			return (data->env[x] + length_of_key + 1);
		}
	}
	return (NULL);
}
/**
 * environment_set_key - overwrite environment variable
 * @key: environment variable
 * By Afua
 * @value: new value
 * @data: struct for program data
 * Return: 1 if params are NULL, 2 on error and 0 on success
 */
int environment_set_key(char *key, char *value, data_of_program *data)
{
	int x, length_of_key = 0, new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);
	length_of_key = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], length_of_key) && data->
				env[x][length_of_key] == '=')
		{
			new_key = 0;
			free(data->env[x]);
			break;
		}
	}
	data->env[x] = str_concat(str_duplicate(key), "=");
	data->env[x] = str_concat(data->env[x], value);

	if (new_key)
	{
		data->env[x + 1] = NULL;
	}
	return (0);
}
/**
 * environment_remove_key - remove key
 * @key: key
 * @data: struct for program data
 * Return: 1 if removed, 0 if not exist
 */
int environment_remove_key(char *key, data_of_program *data)
{
	int x, length_of_key = 0;

	if (key == NULL || data->env == NULL)
		return  (0);
	length_of_key = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], length_of_key) && data
				->env[x][length_of_key] == '=')
		{
			free(data->env[x]);
			x++;
			for (; data->env[x]; x++)
			{
				data->env[x - 1] = data->env[x];
			}
			data->env[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}
/**
 * print_environment - print currrent environment
 * By Afua
 * @data: struct for program data
 */
void print_environment(data_of_program *data)
{
	int y;

	for (y = 0; data->env[y]; y++)
	{
		_print(data->env[y]);
		_print("\n");
	}
}
