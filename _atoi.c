#include "shell.h"

/**
 * alpha_check - verifies on characters that are alphabetical
 * @c: input
 * Return:  One provided c is an alphabetical nature, 0 unless
 */
int alpha_check(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * interactive - yields true if the command line is in an interactive state.
 * @info: structures description
 * Return: One if the mode of operation is interacting, 0 elsewhere
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * convert_to_integer - ransforms the text to an integers
 * @s: the string that needs to be processed
 * Return: If there are indeed no digits in the text,
 * return 0 otherwise, give the resulting amount
 */
int convert_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * delim_check - detects when an element is a delimeter
 * @c: the character that needs that is examined
 * @delim: actual delimeter expression
 * Return: One if true that 0 if not
 */
int delim_check(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

