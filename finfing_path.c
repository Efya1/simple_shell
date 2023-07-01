#include "myshell.h"
/**
 * check_files - check if file exists
 * @file_path: filename
 * By Afua
 * Return: 0 on succes, otherwise error code
 */
int check_files(char *file_path)
{
	struct stat s;

	if (stat(file_path, &s) != -1)
	{
		if (S_ISDIR(s.st_mode) || access(file_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
/**
 * finding_program - find program
 * @data: struct for program data
 * Return: 0 on success, or error code
 */
int finding_program(data_of_program *data)
{
	int x = 0, r_code = 0;
	char **dir;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_files(data->command_name));
	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/")
			, data->command_name);
	if (!data->tokens[0])
		return (2);
	dir = tokenize_paths(data);
	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; dir[x]; x++)
	{
		dir[x] = str_concat(dir[x], data->tokens[0]);
		r_code = check_files(dir[x]);
		if (r_code == 0 || r_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dir[x]);
			free_array_of_pointers(dir);
			return (r_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dir);
	return (r_code);
}
/**
 * tokenize_paths - tokenize
 * @data: program data
 * By Afua
 * Return: array of paths
 */
char **tokenize_paths(data_of_program *data)
{
	int x = 0, count_dir = 2;
	char **tok = NULL, *path;

	path = environment_get_key("PATH", data);
	if ((path == NULL || path[0] == '\0'))
		return (NULL);

	path = str_duplicate(path);
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
			count_dir++;
	}
	tok = malloc(sizeof(char *) * count_dir);
	x = 0;
	tok[x] = str_duplicate(_strtok(path, ":"));
	while (tok[x++])
	{
		tok[x] = str_duplicate(_strtok(NULL, ":"));
	}
	free(path);
	path = NULL;
	return (tok);
}
