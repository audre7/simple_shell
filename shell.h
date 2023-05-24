#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

/* this are for the function for convert numbers  */
#define CONVERT_LOWERCASE
#define CONVERT_UNSIGNED /* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0 1 2
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* the commands used for chainning  */
#define CMD_NORM
#define CMD_OR
#define CMD_AND
#define CMD_CHAIN 0 1 2 3

/* to read and write buffers  */
#define READ_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/**
* struct passinfo - have all the elements that will pass data to the CLI
* @arg: just an argument
* @argv:this is an array of strings gotten from argument
* @path: this is an path gotten from argument
* @argc: the counted argument gotten
* @line_count: the number of errors
* @err_num: if this line of input is counted
* @linecount_flag: the directory name of the program
* @fname: the directory name of the program
* @env: a list of linked files containing a local copy of environ
* @environ: an individualized copy of env's environ
* @history: the pointer for history
* @alias: he node's ID with the alias
* @env_changed: if the conditions has changed
* @status: the response state of the last command executed
* @cmd_buf: address to cmd_buf location, if linking is permitted.

* @cmd_buf: location of cmd_buf pointer, when tying
 * @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: a directory descriptors that is used one is reading line input
*/
typedef struct passinfo
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
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;
/**
 * struct builtin -  includes an integrated text and a function that is connected to it
 * @type:the integrated instruction signal
 * @func: the function being called
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;
#define INFO_INIT                                                               \
    {                                                                           \
        NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
            0, 0, 0                                                             \
    }

extern char **environ;
/**
 * struct liststr - this is for the single linked list
 * @num: placeholder for the number field
 * @str: a valid string
 * @next: the next node point
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error prototypes */
void _printErrorMessage(char *str);                  /*_eputs*/
int _writeErrorCharacter(char c);                    /*_eputchar*/
int _writeCharacterToFileDescriptor(char c, int fd); /*_putfd*/
int _writeStringToFileDescriptor(char *str, int fd); /*_putsfd*/

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

/* the prototypes for exit */
char *custom_strncpy(char *, char *, int); /*_strncpy*/
char *custom_strncat(char *, char *, int); /*_strncat*/
char *custom_strchr(char *, char);         /*_strchr*/

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
int alpha_check(int); /*  _isalpha */
int interactive(info_t *);
int convert_to_integer(char *); /*_atoi*/
int delim_check(char, char *);  /* is_delim */

/* the error uitils prototypes */
int error_handling_atoi(char *);                    /*_erratoi*/
void print_error_info(info_t *, char *);            /*print_error*/
int print_formatted_int(int, int);                  /*print_d*/
char *convert_number_to_string(long int, int, int); /*convert_number*/
void remove_code_comments(char *);                  /*remove_comments*/

/* the first builtin files */
int _shellhelp(info_t *); /*_myhelp*/
int _shellexit(info_t *); /*_myexit*/
int _shellcd(info_t *);   /*_mycd*/

/*  the shell builtins commands  */
int _alias(info_t *);   /*_myalias*/
int _history(info_t *); /*_myhistory*/

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* the information getting prototypes */
void resetInfo(info_t *);               /*clear_info*/
void initializeInfo(info_t *, char **); /*set_info*/
void releaseInfo(info_t *, int);        /*free_info*/

/* environment files */
char *_find_environment_variable(info_t *, const char *); /**_getenv*/
int _shell_environment(info_t *);                         /*_myenv*/
int _shell_set_environment_variable(info_t *);            /*_setenv*/
int _shell_unset_environment_variable(info_t *);          /*_myunsetenv*/
int populate_environment_list(info_t *);                  /*populate_env_list*/

/* the prototype to get all the env's*/
char **getEnvironmentVariables(info_t *);             /*get_environ*/
int unsetEnvironmentVariable(info_t *, char *);       /*_unsetenv*/
int setEnvironmentVariable(info_t *, char *, char *); /*_setenv*/

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

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
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

