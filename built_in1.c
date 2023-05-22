#include "alxse.h"

/**
 * _myhistory - displays history list, one cmd by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential args.
 * Used to maintain constant func prototype.
 *  Return: Always (0)
 */
int _myhistory(pinfo_t *info)
{
print_list(info->history);
return (0);
}

/**
 * unset_alias - sets alias to str
 * @info: parameter for struct
 * @str: the str alias
 *
 * Return: Always (0) on success, (1) on error
 */

int unset_alias(pinfo_t *info, char *str)
{
char *f, c;
int ret;

f = _strchr(str, '=');
if (!f)
	return (1);
c = *f;
*f = 0;
ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*f = c;
return (ret);
}

/**
 * set_alias - sets alias to str
 * @info: parameter for struct
 * @str: the str alias
 *
 * Return: Always (0) on success, (1) on error
 */

int set_alias(pinfo_t *info, char *str)
{
char *f;

f = _strchr(str, '=');
if (!f)
	return (1);
if (!*++f)
	return (unset_alias(info, str));

unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias str
 * @node: alias node
 *
 * Return: Always (0) on success, (1) on error
 */

int print_alias(list_t *node)
{
char *f = NULL, *a = NULL;

if (node)
{
	f = _strchr(node->str, '=');
	for (a = node->str; a <= f; a++)
	_putchar(*a);
	_putchar('\'');
	_puts(f + 1);
	_puts("'\n");
	return (0);
}
return (1);
}

/**
 * _myalias - mimics the alias built_in
 * @info: Structure containing potential args.
 * Used to maintain constant func prototype.
 *  Return: Always (0)
 */

int _myalias(pinfo_t *info)
{
int x = 0;
char *f = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
	node = info->alias;
	while (node)
	{
		print_alias(node);
		node = node->nxt;
	}
	return (0);
}
for (x = 1; info->argv[x]; x++)
{
	f = _strchr(info->argv[x], '=');
	if (f)
		set_alias(info, info->argv[x]);
	else
		print_alias(node_starts_with(info->alias, info->argv[x], '='));
}

return (0);
}
