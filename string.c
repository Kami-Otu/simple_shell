#include "alxse.h"

/**
 * _strlen - func that returns the length of a str
 * @s: the str whose length to check
 *
 * Return: int length of str
*/

int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strns.
 * @s1: the first strn
 * @s2: the second strn
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
{
	if (*s1 != *s2)
		return (*s1 - *s2);
	s1++;
	s2++;
}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - funs that checks if needle starts with haystack
 * @haystack: the strn to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
*/

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
		return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strns
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
*/

char *_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (str);
}
