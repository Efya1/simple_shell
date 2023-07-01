#include "myshell.h"
/**
 * _strtok - separates strings with delimiters
 * By Afua
 * @line: pointer to array we receive in getline.
 * @delimiters: characters we mark off string in parts.
 * Return: pointer to the created token
*/
char *_strtok(char *line, char *delimiters)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delimiters[j] != '\0'; j++)
		{
			if (*str == delimiters[j])
			break;
		}
		if (delimiters[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delimiters[j] != '\0'; j++)
		{
			if (*str == delimiters[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
