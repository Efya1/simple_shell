#include "myshell.h"
/**
 * _getlines - allow to read a line from command prompt
 * By Afua
 * @data: struct containing data of program
 * Return: number of bytes
 */
int _getlines(data_of_program * data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *array_of_commands[10] = {NULL};
	static char array_of_operators[10] = {'\0'};
	ssize_t read_bytes, x = 0;

	/* check if command is in array and logical opeartors */
	if (!array_of_commands[0] || (array_of_operators[0] == '&' && errno != 0) || (
				array_of_operators[0] == '|' && errno == 0))
	{
		/* free allocated memory if exists */
		for (x = 0; array_of_commands[x]; x++)
		{
			free(array_of_commands[x]);
			array_of_commands[x] = NULL;
		}
		/* write to buffer from file descriptor */
		read_bytes = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (read_bytes == 0)
		{
			return (-1);
		}
		x = 0;
		do {
			array_of_commands[x] = str_duplicate(_strtok
					(x ? NULL : buffer, "\n;"));
			x = check_ops_logic(array_of_commands, x, array_of_operators);
		} while (array_of_commands[x++]);
	}

	data->input_line = array_of_commands[0];

	for (x = 0; array_of_commands[x]; x++)
	{
		array_of_commands[x] = array_of_commands[x + 1];
		array_of_operators[x] = array_of_operators[x + 1];
	}

	return (str_length(data->input_line));
}

/**
 * check_ops_logic - check for logical operators and split
 * @array_of_commands: array of various commands
 * @x: index in array of commands being checked
 * @array_of_operators: array of previous command's logical operators
 * Return: index of last command in array of commands
 */
int check_ops_logic(char *array_of_commands[], int x,
		char array_of_operators[])
{
	char *temporary = NULL;
	int y;

	/* check for & in command */
	for (y = 0; array_of_commands[x] != NULL && array_of_commands[x][y]; y++)
	{
		if (array_of_commands[x][y] == '&' && array_of_commands[x][y + 1] == '&')
		{
			/** split line at && */
			temporary = array_of_commands[x];
			array_of_commands[x][y] = '\0';
			array_of_commands[x] = str_duplicate(array_of_commands[x]);
			array_of_commands[x + 1] = str_duplicate(temporary + y + 2);
			x++;
			array_of_operators[x] = '&';
			free(temporary);
		}
		if (array_of_commands[x][y] == '|' && array_of_commands[x][y + 1] == '|')
		{
			/* split line at || */
			temporary = array_of_commands[x];
			array_of_commands[x][y] = '\0';
			array_of_commands[x] = str_duplicate(array_of_commands[x]);
			array_of_commands[x + 1] = str_duplicate(temporary + y + 2);
			x++;
			array_of_operators[x] = '|';
			free(temporary);
			y = 0;
		}
	}
	return (x);
}
