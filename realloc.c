#include "alxse.h"

/**
 * _memset – func that fills memory with a constant byte
 * @s: ptr to the memory area
 * @b: byte to fill *s with
 * @n: amount of bytes to be filled
 *
 * Return: (s) a ptr to the memory area s
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);

/**
 * ffree – func that frees a strn of strns
 * @pp: strn of strns
*/

void ffree(char **pp)
{
	char **w = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
		free(w);
}

/**
 * _realloc – func that reallocates a block of memory
 * @ptr: ptr to previous malloc'ated block
 * @old_size: the byte size of previous block
 * @new_size: the byte size of new block
 *
 * Return: ptr to da ol'block nameen.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *m;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	m = malloc(new_size);
	if (!m)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		m[old_size] = ((char *)ptr)[old_size];
		free(ptr);
	return (m);
}
