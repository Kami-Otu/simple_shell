#include "alxse.h"

/**
 * is_cmd - determines if a file is an executable cmd
 * @info: info struct
 * @path: the path to the file
 *
 * Return: (1) if true, (0) otherwise
*/

int is_cmd(pinfo_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
{
	return (1);
}
	return (0);
}

/**
 * dub_chars - duplicate chars
 * @pathstr: path strn
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: ptr to the new buffer
*/

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, l = 0;

	for (l = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[l++] = pathstr[x];
	buf[l] = 0;
	return (buf);
}

/**
 * find_path - func that finds this cmd in the path strn
 * @info: the info struct
 * @pathstr: PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
*/

char *find_path(pinfo_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
	if (is_cmd(info, cmd))
		return (cmd);
}
	while (1)
{
	if (!pathstr[x] || pathstr[x] == ':')
	{
		path = dup_chars(pathstr, curr_pos, x);
		if (!*path)
			_strcat(path, cmd);
		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}
		if (is_cmd(info, path))
			return (path);
		if (!pathstr[x])
			break;
		curr_pos = x;
	}
	x++;
}
	return (NULL);
}
