#include "myshell.h"
/**
 * list_of_builtins - search and execute builtins match
 * By Afua
 * @data: struct for program data
 * Return: function executed of -1 on failure
 */
int list_of_builtins(data_of_program *data)
{
	int i;
	builtins options[] = {
		{"exit", exit_builtin},
		{"help", help_builtin},
		{"cd", cd_builtin},
		{"alias", alias_builtin},
		{"env", builtin_environment},
		{"setenv", builtin_set_environment},
		{"unsetenv", builtin_unset_environment},
		{NULL, NULL}
	};
	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (str_compare(options[i].builtin, data->command_name, 0))
		{
			return (options[i].function(data));
		}
	}
	return (-1);
}
