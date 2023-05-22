#include "alxse.h"

/**
 * _eputs - prints input str
 * @str: the str to be printed
 *
 * Return: nil
 */

void _eputs(char *str)
{
int j = 0;

if (!str)
	return;
while (str[j] != '\0')
{
	_eputchar(str[j]);
	j++;
}
}

/**
 * _eputchar - writes char c to stderr
 * @c: The char to print
 *
 * Return: (1) Success.
 * On error, (-1) is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
static int j;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
	write(2, buf, j);
	j = 0;
}
if (c != BUF_FLUSH)
	buf[j++] = c;
return (1);
}

/**
 * _putfd - writes char c to given fd
 * @c: The char to print
 * @fd: The filedescriptor to write to
 *
 * Return: (1) success.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
static int j;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
	write(fd, buf, j);
	j = 0;
}
if (c != BUF_FLUSH)
	buf[j++] = c;
return (1);
}

/**
 * _putsfd - prints input str
 * @str: str to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */

int _putsfd(char *str, int fd)
{
int j = 0;

if (!str)
	return (0);
while (*str)
{
	j += _putfd(*str++, fd);
}
return (j);
}
