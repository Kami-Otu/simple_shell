#include "alxse.h"

/**
 * is_chain - test if current char in the buffer is a chain delimete
 * @info: parameter struct
 * @buf: char buffer
 * @p: the address of current position in buf
 *
 * Return: (1) if chain delimeter, (0) otherwise
*/

int is_chain(pinfo_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
{
	buf[i] = 0;
	i++;
	info->cmd_buf_type = CMD_OR;
}
	else if (buf[i] == '&' && buf[i + 1] == '&')
{
	buf[i] = 0;
	i++;
	info->cmd_buf_type = CMD_AND;
}
	else if (buf[i] == ';') /* found end of this command */
{
	buf[i] = 0; /* replace semicolon with null */
	info->cmd_buf_type = CMD_CHAIN;
}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - checks we should cont. chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: the address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 *
 * Return: Void
*/

void check_chain(pinfo_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
{
	if (info->status)
	{
		buf[i] = 0;
		m = len;
	}
}
	if (info->cmd_buf_type == CMD_OR)
{
	if (!info->status)
	{
		buf[i] = 0;
		m = len;
	}
}

	*p = m;
}

/**
 * replace_alias - func that replaces aliases in tokenized str
 * @info: parameter struct
 *
 * Return: (1) if replaced, (0) otherwise
*/

int replace_alias(pinfo_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
{
	node = node_starts_with(info->alias, info->argv[0], '=');
	if (!node)
		return (0);
	free(info->argv[0]);
	p = _strchr(node->str, '=');
	if (!p)
		return (0);
	p = _strdup(p + 1);
	if (!p)
		return (0);
	info->argv[0] = p;
}
	return (1);
}

/**
 * replace_vars - func that replaces vars in tokenized str
 * @info: parameter struct
 *
 * Return: (1) if replaced, (0) otherwise
*/

int replace_vars(pinfo_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
{
	if (info->argv[x][0] != '$' || !info->argv[x][1])
		continue;

	if (!_strcmp(info->argv[x], "$?"))
	{
		replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
		continue;
	}
	if (!_strcmp(info->argv[x], "$$"))
	{
		replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
		continue;
	}
	node = node_starts_with(info->env, &info->argv[x][1], '=');
	if (node)
	{
		replace_string(&(info->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
		continue;
	}
	replace_string(&info->argv[x], _strdup(""));

}
	return (0);
}

/**
 * replace_string - func that replaces string
 * @old: the address of old string
 * @new: the new string
 *
 * Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

