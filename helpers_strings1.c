#include "myshell.h"

/**
 * str_length - returns the length of a null terminated string.
 * By Afua
 * @str: pointer to string.
 * Return: length of string.
 */
int str_length(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);

	while (str[length++] != '\0')
	{
	}
	return (--length);
}


/**
 * str_duplicate - duplicates a string
 * @str: String to be duplicated
 * Return: pointer to the array
 * By Afua
 */
char *str_duplicate(char *str)
{
	char *result;
	int length, i;

	if (str == NULL)
		return (NULL);

	length = str_length(str) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = str[i];
	}

	return (result);
}

/**
 * str_compare - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_compare(char *str1, char *str2, int number)
{
	int iterator;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_length(str1) != str_length(str2))
			return (0);
		for (iterator = 0; str1[iterator]; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (str1[iterator] != str2[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concat(char *str1, char *str2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (str1 == NULL)
		str1 = "";
	length1 = str_length(str1);

	if (str2 == NULL)
		str2 = "";
	length2 = str_length(str2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; str1[length1] != '\0'; length1++)
		result[length1] = str1[length1];
	free(str1);

	for (length2 = 0; str2[length2] != '\0'; length2++)
	{
		result[length1] = str2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 * By Afua
 *
 * @str: pointer to string.
 * Return: void.
 */
void str_reverse(char *str)
{

	int i = 0, length = str_length(str) - 1;
	char hold;

	while (i < length)
	{
		hold = str[i];
		str[i++] = str[length];
		str[length--] = hold;
	}
}
