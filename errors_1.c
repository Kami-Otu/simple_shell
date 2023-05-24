#include "alxse.h"

/**
 * _erratoi - converts str to an int
 * @s: the str to be converted
 * Return: (0) if no numbers in string, converted number otherwise
 * -1 on error
 */

int _erratoi(char *s)
{
int j = 0;
unsigned long int result = 0;

if (*s == '+')
	s++;  /* TODO: why does this make main return 255? */
for (j = 0;  s[j] != '\0'; j++)
{
	if (s[j] >= '0' && s[j] <= '9')
	{
		result *= 10;
		result += (s[j] - '0');
		if (result > INT_MAX)
			return (-1);
	}
	else
		return (-1);
}
return (result);
}

/**
 * print_error - prints err message
 * @info: parameter & return info struct
 * @estr: str containing specified err type
 * Return: (0) if no nums in str, converted num otherwise
 * -1 on error
 */

void print_error(pinfo_t *info, char *estr)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
 * print_d - func prints a decimal (int) number (base 10)
 * @input: the input
 * @fd: filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int j, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
	__putchar = _eputchar;
if (input < 0)
{
	_abs_ = -input;
	__putchar('-');
	count++;
}
else
	_abs_ = input;
current = _abs_;
for (j = 1000000000; j > 1; j /= 10)
{
	if (_abs_ / j)
	{
		__putchar('0' + current / j);
		count++;
	}
	current %= j;
}
__putchar('0' + current);
count++;

return (count);
}

/**
 * convert_number - converter func, a clone of itoa
 * @number: the number
 * @base: base
 * @flags: arg flags
 *
 * Return: str
 */

char *convert_number(long int number, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = number;

if (!(flags & CONVERT_UNSIGNED) && number < 0)
{
	n = -number;
	sign = '-';

}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do	{
	*--ptr = array[n % base];
	n /= base;
} while (n != 0);

if (sign)
	*--ptr = sign;
return (ptr);
}

/**
 * remove_comments - func replaces first instance of '#' with '\0'
 * @buf: address of the str to modify
 *
 * Return: Always (0);
 */

void remove_comments(char *buf)
{
int j;

for (j = 0; buf[j] != '\0'; j++)
	if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
	{
		buf[j] = '\0';
		break;
	}
}
