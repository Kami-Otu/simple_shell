#include "alxse.h"

/**
 * **strtow - splits a str into words. Repeat delimiters are ignored
 * @str: input str
 * @d: delimeter str
 *
 * Return: a ptr to an arr of strns, or NULL on failure
 */

char **strtow(char *str, char *d)
{
int i, j, k, m, numwords = 0;
char **h;

if (str == NULL || str[0] == 0)
	return (NULL);
if (!d)
	d = " ";
for (i = 0; str[i] != '\0'; i++)
	if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
		numwords++;

if (numwords == 0)
	return (NULL);
h = malloc((1 + numwords) * sizeof(char *));
if (!h)
	return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
	while (is_delim(str[i], d))
		i++;
	k = 0;
	while (!is_delim(str[i + k], d) && str[i + k])
		k++;
	h[j] = malloc((k + 1) * sizeof(char));
	if (!h[j])
	{
		for (k = 0; k < j; k++)
			free(h[k]);
		free(h);
		return (NULL);
	}
	for (m = 0; m < k; m++)
		h[j][m] = str[i++];
	h[j][m] = 0;
}
h[j] = NULL;
return (h);
}

/**
 * **strtow2 - func that splits a strn into words
 * @str: input strn
 * @d: delimeter
 *
 * Return: a ptr to an arr of strns, or NULL on failure
 */

char **strtow2(char *str, char d)
{
int i, j, k, m, numwords = 0;
char **h;

if (str == NULL || str[0] == 0)
	return (NULL);
for (i = 0; str[i] != '\0'; i++)
	if ((str[i] != d && str[i + 1] == d) ||
			    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
		numwords++;
if (numwords == 0)
	return (NULL);
h = malloc((1 + numwords) * sizeof(char *));
if (!h)
	return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
	while (str[i] == d && str[i] != d)
		i++;
	k = 0;
	while (str[i + k] != d && str[i + k] && str[i + k] != d)
		k++;
	h[j] = malloc((k + 1) * sizeof(char));
	if (!h[j])
	{
		for (k = 0; k < j; k++)
			free(h[k]);
		free(h);
		return (NULL);
	}
	for (m = 0; m < k; m++)
		h[j][m] = str[i++];
	h[j][m] = 0;
}
h[j] = NULL;
return (h);
}
