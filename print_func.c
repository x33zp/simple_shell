#include "shell.h"

/**
 * _print - prints the error and input.
 *
 * @f_d: the file discriptor of the output.
 * @format: the constant identifier.
 *
 * Return: void.
 */
void _print(int f_d, const char *format, ...)
{
	int i = -1;
	va_list va;

	va_start(va, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
			case 's':
				print_string(va, f_d);
				break;
			case 'd':
				print_int(va_arg(va, int), f_d);
				break;
			default:
				break;
			}
			i++;
		}
		else
			_putchar(format[i], f_d);
	}
	va_end(va);
}

/**
 * print_string - prints the string to deal with.
 *
 * @f_d: the file discrptor of the input.
 * @va: the variadic arg list.
 *
 * Return: void.
 */
void print_string(va_list va, int f_d)
{
	char *str = NULL;
	int i = -1;

	str = va_arg(va, char *);
	while (str[++i])
		_putchar(str[i], f_d);
}

/**
 * print_int - prints an integer to the stdout.
 *
 * @f_d: the file discriptor of the output.
 * @a: the number to be printed.
 *
 * Return: void.
 */
void print_int(int a, int f_d)
{
	if (a < 10)
		_putchar(a + '0', f_d);
	else
	{
		print_int(a / 10, f_d);
		_putchar(a % 10, f_d);
	}
}
/**
 * _putchar - prints a character literal.
 *
 * @f_d: the file discriptor of the output.
 * @ch: the char to print.
 *
 * Return: void.
 */
void _putchar(char ch, int f_d)
{
	write(f_d, &ch, 1);
}
