#include "alxse.h"

/**
 * _strcpy - copies a str
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
*/

char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
{
	dest[x] = src[x];
	x++;
}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a strn
 * @str: strn to duplicate
 *
 * Return: pointer to the duplicated string
*/

char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - func that prints an input strn
 * @str: strn to be printed
 *
 * Return: Nothing
*/

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
{
	_putchar(str[x]);
	x++;
}
}

/**
 * _putchar - writes the char c to stdout
 * @c: char to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
		return (1);
}
