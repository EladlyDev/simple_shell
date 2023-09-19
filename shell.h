#ifndef _SHELL_H
#define _SHELL_H

/* Standard Libraries */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>


/* Structures */
/**
* struct node_s - node in a linked list.
* @value: the value
* @next: the next node
**/
typedef struct node_s
{
	char *value;
	struct node_s *next;
} node_t;

/**
 * struct shellstate - struct to save the shell state
 * to help print the error message
 * @should_exit: flag used when exit command is entered
 * @exit_status: used to determine the exit status from 0-255
 */
typedef struct shellstate
{
	int should_exit;
	int exit_status;
} ShellState;

/* Macros */
extern char **environ;

/* Prototypes */
int execute(char *pathname, char **av, char **env);
int search_path(char **pathname);
/* 0-string.c */
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
/* 1-string.c */
char *_strtok(char *str, char *delim);
char *_strncpy(char *dest, char *src, int n);
void int_to_str(int n, char *buffer);
/* 0-utils.c */
char *itos(unsigned long n);
node_t *link_path(void);
node_t *new_node(node_t **head, char *value);
char *_getenv(char *var);
void free_list(node_t *head);
/* 1-utils.c */
int error(char **mav, int count, char **cav, char *buff, char *src);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int getokens(char *buff, char **dest, char *delim);
int noftokens(char *buff, char *delim);
void handle_exit_status(char **av);
/* 2-utils.c */
int execute_commands(char ***commands, char **env, char **argv,
					size_t promptNo);
int execute_single_command(char **av, char **env, char **argv,
							size_t promptNo);
int handle_input(char *buff, char **av, char ***commands, char **env,
				char **argv, size_t promptNo);
char **prep_command(char *buff);
char ***prep_commands(char *buff, int nofcommands);
/* 3-utils.c */
void exit_err(char **mav, char *countStr, char **cav);
void exec_err(char **mav, char *countStr, char **cav);

/* exit_env */
int print_env(char *buff);
int check_exit(char *av, ShellState *state);
void check_dollar(char *av, ShellState *state);
void replace_dollar(char *av, ShellState *state);

#endif /* _SHELL_H */
