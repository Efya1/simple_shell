#include "myshell.h"
/**
 * output_alias - to add, remove or show aliases
 * By Afua and Christabel
 * @data: struct for program data
 * @alias: alias to be output
 * Return: 0 on success, other if declared
 */
int output_alias(data_of_program *data, char *alias)
{
	int x, y, length_of_alias;
	char buff[250] = {'\0'};

	if (data->alias_list)
	{
		length_of_alias = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x]
				, alias, length_of_alias) && data->alias_list
						[x][length_of_alias] == '='))
			{
				for (y = 0; data->alias_list[x][y]; y++)
				{
					buff[y] = data->alias_list[x][y];
					if (data->alias_list[x][y] == '=')
						break;
				}
				buff[y + 1] = '\0';
				add_to_buffer(buff, "'");
				add_to_buffer(buff, data->alias_list[x] + y + 1);
				add_to_buffer(buff, "'\n");
				_print(buff);
			}
		}
	}
	return (0);
}
/**
 * fetch_alias - get the alias
 * @data: struct for program data
 * @name: name of alias
 * Return: 0 on success, other if declared
 */
char *fetch_alias(data_of_program *data, char *name)
{
	int x, length_of_alias;

	/** check for nulls */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);
	length_of_alias = str_length(name);
	for (x = 0; data->alias_list[x]; x++)
	{
		if (str_compare(name, data->alias_list[x]
					, length_of_alias) && data->alias_list[x][length_of_alias] == '=')
		{
			return (data->alias_list[x] + length_of_alias + 1);
		}
	}
	return (NULL);
}
/**
 * write_alias - add alias
 * @string_alias: alias
 * @data: struct for program data
 * Return: o on success, other if declared
 */
int write_alias(char *string_alias, data_of_program *data)
{
	int x, y;
	char buff[250] = {'0'}, *temporary = NULL;

	/* check for nulls */
	if (string_alias == NULL || data->alias_list == NULL)
		return (1);
	for (x = 0; string_alias[x]; x++)
	{
		if (string_alias[x] != '=')
			buff[x] = string_alias[x];
		else
		{
			temporary = fetch_alias(data, string_alias + x + 1);
			break;
		}
	}
	for (y = 0; data->alias_list[y]; y++)
	{
		if (str_compare(buff, data->alias_list[y]
					, x) && data->alias_list[y][x] == '=')
		{
			free(data->alias_list[y]);
			break;
		}
	}
	if (temporary)
	{
		add_to_buffer(buff, "=");
		add_to_buffer(buff, temporary);
		data->alias_list[y] = str_duplicate(buff);
	}
	else
		data->alias_list[y] = str_duplicate(string_alias);
	return (0);
}
