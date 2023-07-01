#include "myshell.h"
/**
 * variables_expansion - expand variables
 * By Afua
 * @data: struct for program data
 */
void variables_expansion(data_of_program *data)
{
	int x, y;
	char lines[BUFFER_SIZE] = {0}, expansions[BUFFER_SIZE] = {'\0'}
		, *temporary;

	if (data->input_line == NULL)
		return;

	add_to_buffer(lines, data->input_line);
	for (x = 0; lines[x]; x++)
		if (lines[x] == '#')
			lines[x--] = '\0';
		else if (lines[x] == '$' && lines[x + 1] == '?')
		{
			lines[x] = '\0';
			long_to_string(errno, expansions, 10);
			add_to_buffer(lines, expansions);
			add_to_buffer(lines, data->input_line + x + 2);
		}
		else if (lines[x] == '$' && (lines[x + 1] == ' ' || lines[x + 1] == '\0'))
			continue;
		else if (lines[x] == '$')
		{
			for (y = 1; lines[x + y] && lines[x + y] != ' '; y++)
				expansions[y - 1] = lines[x + y];
			temporary = environment_get_key(expansions, data);
			lines[x] = '\0', expansions[0] = '\0';
			add_to_buffer(expansions, lines + x + y);
			temporary ? add_to_buffer(lines, temporary) : 1;
			add_to_buffer(lines, expansions);
		}
	if (!str_compare(data->input_line, lines, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(lines);
	}
}
/**
 * alias_expansion - expand alias
 * @data: struct for program data
 */
void alias_expansion(data_of_program *data)
{
	int x, y, expanded = 0;
	char lines[BUFFER_SIZE] = {0}, expansions[BUFFER_SIZE] = {'\0'}
		, *temporary;

	if (data->input_line == NULL)
		return;
	add_to_buffer(lines, data->input_line);

	for (x = 0; lines[x]; x++)
	{
		for (y = 0; lines[x + y] && lines[x + y] != ' '; y++)
			expansions[y] = lines[x + y];
		expansions[y] = '\0';

		temporary = fetch_alias(data, expansions);
		if (temporary)
		{
			expansions[0] = '\0';
			add_to_buffer(expansions, lines + x + y);
			lines[x] = '\0';
			add_to_buffer(lines, temporary);
			lines[str_length(lines)] = '\0';
			add_to_buffer(lines, expansions);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(lines);
	}
}
/**
 * add_to_buffer - append to buffer
 * @buffer: buffer
 * By Afua
 * @strings: string to add
 * Return: length
 */
int add_to_buffer(char *buffer, char *strings)
{
	int len, x;

	len = str_length(buffer);
	for (x = 0; strings[x]; x++)
		buffer[len + x] = strings[x];
	buffer[len + x] = '\0';
	return (len + x);
}

