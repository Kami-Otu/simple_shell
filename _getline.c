#include "alxse.h"

/**
 * input_buf - buffers chained cmds
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes that have been read
 */
ssize_t input_buf(pinfo_t *info, char **buf, size_t *len)
{
ssize_t h = 0;
size_t len_p = 0;

if (!*len) /* if there’s nothing left in the buffer, fill it */
{
	/*bfree((void **)info->cmd_buf);*/
	free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	h = getline(buf, &len_p, stdin);
#else
	h = _getline(info, buf, &len_p);
#endif
	if (h > 0)
	{
		if ((*buf)[h - 1] == '\n')
		{
			(*buf)[h - 1] = '\0'; /* remove trailing newline(s) */
			h--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		/* if (str_chr(*buf, ';')) is this a command chain? */
		{
			*len = h;
			info->cmd_buf = buf;
		}
	}
}
return (h);
}

/**
 * get_input - gets line minus the newline
 * @info: parameter struct
 *
 * Return: bytes that have been read
 */

ssize_t get_input(pinfo_t *info)
{
static char *buf;/* the ';' command chain buffer */
static size_t i, j, len;
ssize_t h = 0;
char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH);
h = input_buf(info, &buf, &len);
if (h == -1) /* End Of File (EOF) */
	return (-1);
if (len) /* commands left in the chain buffer */
{
	j = i; /* init new iterator to the current buf position */
	p = buf + i; /* get pointer for return */

	check_chain(info, buf, &j, i, len);
	while (j < len) /* iterate to semicolon or end */
	{
		if (is_chain(info, buf, &j))
			break;
		j++;
	}

	i = j + 1; /* increment past nulled ';'' */
	if (i >= len) /* reached end of buffer? */
	{
		i = len = 0; /* reset position and length */
		info->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p; /* pass back pointer to current command position */
	return (_strlen(p)); /* return length of current command */
}

*buf_p = buf; /* else its not a chain, pass back d buffer from _getline() */
return (h); /* return length of buffer from the _getline() */
}

/**
 * read_buf - func that reads a buffer from _getline
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: h
 */
ssize_t read_buf(pinfo_t *info, char *buf, size_t *i)
{
ssize_t h = 0;

if (*i)
	return (0);
h = read(info->readfd, buf, READ_BUF_SIZE);
if (h >= 0)
	*i = h;
return (h);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: the parameter struct
 * @ptr: address of the ptr to buffer, preallocated or NULL(\0)
 * @length: size of the preallocated ptr buffer if not NULL(\0)
 *
 * Return: s
 */

int _getline(pinfo_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
	s = *length;
if (i == len)
	i = len = 0;

r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
	return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
	return (p ? free(p), -1 : -1);

if (s)
	_strncat(new_p, buf + i, k - i);
else
	_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
	*length = s;
*ptr = p;
return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
