#include "alxse.h"

/**
 * list_len - determines the lenght of linked list
 * @h: the ptr to first node
 *
 * Return: the size of list
*/

size_t list_len(const list_t *h)
{
size_t t = 0;

while (h)
{
	h = h->nxt;
	t++;
}
return (t);
}

/**
 * list_to_strings - func that returns an arr of strns
 *of the list->str
 * @head: the ptr to first node
 *
 * Return: the array of strings
*/

char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t t = list_len(head), j;
char **strs;
char *str;

if (!head || !t)
	return (NULL);
strs = malloc(sizeof(char *) * (t + 1));
if (!strs)
	return (NULL);
for (t = 0; node; node = node->nxt, t++)
{
	str = malloc(_strlen(node->str) + 1);
	if (!str)
	{
		for (j = 0; j < t; j++)
			free(strs[j]);
		free(strs);
		return (NULL);
	}

	str = _strcpy(str, node->str);
	strs[t] = str;
}
strs[t] = NULL;
return (strs);
}

/**
 * print_list - func that prints all elements of
 * a list_t linked list
 * @h: the ptr to first node
 *
 * Return: size of list
*/

size_t print_list(const list_t *h)
{
size_t t = 0;

while (h)
{
	_puts(convert_number(h->number, 10, 0));
	_putchar(':');
	_putchar(' ');
	_puts(h->str ? h->str : "(nil)");
	_puts("\n");
	h = h->nxt;
	t++;
}
return (t);
}

/**
 *  node_starts_with - returns node whose str starts with prefix
 *  @node: the ptr to the list head
 *  @prefix: the strn to match
 *  @c: nxt char after prefix to match
 *
 * Return: the match node or null
*/

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
	p = starts_with(node->str, prefix);
	if (p && ((c == -1) || (*p == c)))
		return (node);
	node = node->nxt;
}
return (NULL);
}

/**
 * get_node_index - function that gets the index of a node
 * @head: the ptr to the list head
 * @node: the ptr to the node
 *
 * Return: index of node or -1
*/

ssize_t get_node_index(list_t *head, list_t *node)
{
size_t t = 0;

while (head)
{
	if (head == node)
		return (t);
	head = head->nxt;
	t++;
}
return (-1);
}
