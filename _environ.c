#include "alxse.h"

/**
 * _myenv - prints current environment
 * @info: Structure containing potential args.
 * Used to maintain constant function prototype.
 * Return: Always (0)
 */

int _myenv(pinfo_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * _getenv - gets value of an environ variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(pinfo_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
	p = starts_with(node->str, name);
	if (p && *p)
		return (p);
	node = node->nxt;
}
return (NULL);
}

/**
 * _mysetenv - Initializes new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *  Return: Always (0)
 */

int _mysetenv(pinfo_t *info)
{
if (info->argc != 3)
{
	_eputs("Incorrect number of arguements\n");
	return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
return (1);
}

/**
 * _my_unset_env - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always (0)
 */

int _my_unset_env(pinfo_t *info)
{
int j;

if (info->argc == 1)
{
	_eputs("Too few arguements.\n");
	return (1);
}
for (j = 1; j <= info->argc; j++)
	_unsetenv(info, info->argv[j]);

return (0);
}

/**
 * populate_env_list - populates the env linked list
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always (0)
 */
int populate_env_list(pinfo_t *info)
{
list_t *node = NULL;
size_t j;

for (j = 0; environ[j]; j++)
	add_node_end(&node, environ[j], 0);
info->env = node;
return (0);
}
