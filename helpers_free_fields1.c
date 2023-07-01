#include "myshell.h"

/**
 * free_recurrent_data - free the fields needed for each loop of a program
 * By Afua
 * @data: structure of the program's data
 * Return: Nothing
 */
void free_recurrent_data(data_of_program *data)
{
	if (data)
	{
		if (data->tokens)
		{
			free_array_of_pointers(data->tokens);
			data->tokens = NULL;
		}
		if (data->input_line)
		{
			free(data->input_line);
			data->input_line = NULL;
		}
		if (data->command_name)
		{
			free(data->command_name);
			data->command_name = NULL;
		}
	}
}

/**
  *free_all_data - free all fields of a program
  *@data: struct of the program's data
  *Return: Nothing
  */
void free_all_data(data_of_program *data)
{
	if (data)
	{
		if (data->file_descriptor != 0)
		{
			if (close(data->file_descriptor) == -1)
			{
				perror(data->program_name);
			}
		}
		free_recurrent_data(data);
		if (data->env)
		{
			free_array_of_pointers(data->env);
		}
		if (data->alias_list)
		{
			free_array_of_pointers(data->alias_list);
		}
	}
}

/**
  *free_array_of_pointers - free an array of pointers
  *@array: array of pointers
 * By Afua
  *Return: nothing
  */
void free_array_of_pointers(char **array)
{
	int i;

	if (array == NULL)
	{
		return;
	}

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}

	free(array);
	array = NULL;
}
