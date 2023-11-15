#include "shell.h"

/**
 * _strcmp - it will compare the strings in the first place.
 *
 * @s1: the first  string.
 * @s2: the second string.
 *
 * Return: 0 - if they are not equal, 1 - if they are equal.
 */
int _strcmp(char *s1, char *s2)
{
	int i = -1;

	if (_strlen(s1) == _strlen(s2))
	{
		while (s1[++i])
		{
			if (s1[i] != s2[i])
				return (0);
		}
		return (1);
	}
	return (0);
}

/**
 * _strlen - calculates the string length of the char arr.
 *
 * @s: the string to be calculated.
 *
 * Return: the length of the string always.
*/
int _strlen(char *s)
{
	int i = -1, len = 0;

	while (s[++i])
		len++;

	return (len);
}

/**
 * _strconc - this is the function to conacatinate string.
 *
 * @src: this is the source of the string.
 * @dest: this the the destnation for the needed str.
 *
 * Return: void.
*/
char  *_strconc(char *dest, char *src)
{
	int len = _strlen(dest), i = -1;

	while (src[++i])
	{
		dest[len] = src[i];
		len++;
	}
	dest[len] = '\0';

	return (dest);
}

/**
 * process_cmd - is like the string tokenizer.
 *
 * @cmd: is the command get from the user.
 *
 * Return: a char pointer to pointer.
*/
char **process_cmd(char *cmd)
{
	int i = -1, section = 0;
	char **cmd_collec;

	while (cmd[++i])
	{
		if (cmp(cmd[i]))
			section++;
	}
	section++;

	cmd_collec = (char **)malloc(sizeof(char *) * (section + 1));
	if (cmd_collec == NULL)
	{
		perror("Memory allocation fails\n");
		exit(1);
	}

	i = -1, cmd_collec[0] = cmd, section = 1;
	while (cmd[++i])
	{
		if (cmp(cmd[i]))
		{
			cmd[i] = '\0';
			if (!cmd[i + 1])
				continue;
			cmd_collec[section] = &cmd[i + 1];
			i++, section++;
		}
	}
	cmd_collec[section] = NULL;

	return (cmd_collec);
}

/**
 * unconcat - unconcatnates string.
 *
 * @dest: the destnation of the copy.
 * @str: the string to remove.
 *
 * Return: a pointer to a char.
*/
char *unconcat(char *dest, char *str)
{
	int len = _strlen(dest), len2 = _strlen(str);

	len -= len2;

	dest[len + 1] = '\0';

	return (dest);
}
