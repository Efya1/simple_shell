#include <stdio.h>
#include "myshell.h"
/**
 * print_prompt - prints a prompt followed by a space
 * By Afua
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
