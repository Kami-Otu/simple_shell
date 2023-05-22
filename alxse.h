#ifndef _ALXSE_H_
#define _ALXSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* to read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* to command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* to convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr – singly-linked list
 * @number: the number field
 * @str: a string
 * @nxt: points to the next node
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *nxt;
} list_t;

/**
 * struct info - contains pseudo-args to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing args
 * @argv:an array of strs generated from arg
 * @path: a str path for the current command
 * @argc: the arg count
 * @line_count: the err count
 * @err_num: the err code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} pinfo_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a built-in string and related functions
 * @type: the built-in command flag
 * @funct: the function
 */
typedef struct builtin
{
	char *type;
	int (*funct)(pinfo_t *);
} builtin_t;

/* toem_shloop.c */
int hsh(pinfo_t *, char **);
int find_builtin(pinfo_t *);
void find_cmd(pinfo_t *);
void fork_cmd(pinfo_t *);

/* toem_parser.c */
int is_cmd(pinfo_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(pinfo_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(pinfo_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(pinfo_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(pinfo_t *);
int _mycd(pinfo_t *);
int _myhelp(pinfo_t *);

/* toem_builtin1.c */
int _myhistory(pinfo_t *);
int _myalias(pinfo_t *);
int unset_alias(pinfo_t *info, char *str);
int set_alias(pinfo_t *info, char *str);
int print_alias(list_t *node);

/*toem_getline.c */
ssize_t input_buf(pinfo_t *info, char **buf, size_t *len);
ssize_t get_input(pinfo_t *);
ssize_t read_buf(pinfo_t *info, char *buf, size_t *i);
int _getline(pinfo_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(pinfo_t *);
void set_info(pinfo_t *, char **);
void free_info(pinfo_t *, int);

/* toem_environ.c */
char *_getenv(pinfo_t *, const char *);
int _myenv(pinfo_t *);
int _mysetenv(pinfo_t *);
int _my_unset_env(pinfo_t *);
int populate_env_list(pinfo_t *);

/* toem_getenv.c */
char **_getenviron(pinfo_t *);
int _unsetenv(pinfo_t *, char *);
int _setenv(pinfo_t *, char *, char *);

/* toem_history.c */
char *get_history_file(pinfo_t *info);
int write_history(pinfo_t *info);
int read_history(pinfo_t *info);
int build_history_list(pinfo_t *info, char *buf, int linecount);
int renumber_history(pinfo_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(pinfo_t *, char *, size_t *);
void check_chain(pinfo_t *, char *, size_t *, size_t, size_t);
int replace_alias(pinfo_t *);
int replace_vars(pinfo_t *);
int replace_string(char **, char *);

#endif
