#include "alxse.h"

/**
 * add_node – func to add a node to the start of the list
 * @head: the address of ptr to head node
 * @str: string field of node
 * @number: node index used by history
 *
 * Return: the size of list
*/

list_t *add_node(list_t **head, const char *str, int number)
{
	list_t *new_head;

	if (!head)
	return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
	return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->number = number;
	if (str)
{
	new_head->str = _strdup(str);
	if (!new_head->str)
	{
		free(new_head);
		return (NULL);
	}
}
	new_head->nxt = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 *
 * Return: size of list
*/

list_t *add_node_end(list_t **head, const char *str, int number)
{
	list_t *new_node, *node;

	if (!head)
	return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (str)
{
	new_node->str = _strdup(str);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}
}
	if (node)
{
	while (node->nxt)
		node = node->nxt;
	node->nxt = new_node;
}
	else
	*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the string element of a list_t linked list
 * @h: the pointer to first node
 *
 * Return: the size of list
*/

size_t print_list_str(const list_t *h)
{
	size_t r = 0;

	while (h)
{
	_puts(h->str ? h->str : "(nil)");
	_puts("\n");
	h = h->nxt;
	r++;
}
	return (r);
}

/**
 * delete_node_at_index – func that deletes node at given index
 * @head: the address of pointer to first node
 * @index: the index of node to delete
 *
 * Return: (1) success & (0) failure
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!head || !*head)
	return (0);

	if (!index)
{
	node = *head;
	*head = (*head)->nxt;
	free(node->str);
	free(node);
	return (1);
}
	node = *head;
	while (node)
{
	if (x == index)
	{
		prev_node->nxt = node->nxt;
		free(node->str);
		free(node);
		return (1);
	}
	x++;
	prev_node = node;
	node = node->nxt;
}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
*/
void free_list(list_t **head_ptr)
{
	list_t *node, *nxt_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
{
	nxt_node = node->nxt;
	free(node->str);
	free(node);
	node = nxt_node;
}
	*head_ptr = NULL;
}
