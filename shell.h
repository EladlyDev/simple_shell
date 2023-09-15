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

extern char **environ;

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
char **_strtok(char *str, char *delim, char **arr);
size_t noftokens(char *str, char *delim);

/* 0-utils.c */
char *itos(unsigned long n);
node_t *link_path(void);
node_t *new_node(node_t **head, char *value);
char *_getenv(char *var);
void free_list(node_t *head);

/* 1-utils.c */
void error(char *mav, int count, char *cav, char *src);

#endif /* _SHELL_H */
