#include "shell.h"

/**
 * remove_delim - it ignores a space and returns the character.
 *
 * @str: is the character pointer.
 *
 * Return: the new array of chars
 */
char *remove_delim(char *str)
{
	int i = 0, j = 0;
	char *arr = NULL;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	arr = malloc(sizeof(char) * (_strlen(str) + 1));
	if (cmp(str[0]))
		while (cmp(str[i]))
			i++;
	while (str[i])
	{
		if (!cmp(str[i]))
			arr[j] = str[i], j++, i++;
		else if (cmp(str[i]))
		{
			arr[j] = ' ', j++;
			while (cmp(str[i]))
				i++;
		}
	}
	arr[j] = '\0';

	free(str);
	return (arr);
}

/**
 * cmp - compares character.
 *
 * @a: the chracter to be compared.
 *
 * Return: the comparision details.
*/
int cmp(char a)
{
	char *delim = " \t\n";

	if (a == delim[1] || a == delim[2] || a == delim[0])
		return (1);
	return (0);
}

/**
 * extract_int - extracts the integer passed as parameter for exit.
 *
 * @intger: is the exit parameter.
 *
 * Return: a posetive num in success, -1 if ohter char is encountered.
*/
int extract_int(char *intger)
{
	int num = 0, i = -1;

	while (intger[++i])
	{
		if (intger[i] >= 48 && intger[i] <= 57)
			num = num * 10 + ((int)intger[i] - 48);
		else
			return (-1);
	}

	return (num);
}

/**
 * concat_to_current - it will concatnates to the current str.
 *
 * @instrction: is the executable name.
 * @cur_dir: the current directory name.
 *
 * Return: pointer to concatnated string.
*/
char *concat_to_current(char *instrction, char *cur_dir)
{
	return (_strconc(cur_dir, (instrction + 1)));
}
