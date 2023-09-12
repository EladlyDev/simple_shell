#include "shell.h"

/**
 * itos - converts a number into a string
 * @n: number to be converted
 *
 * Return: a pointer to the string
 **/

char *itos(unsigned long n)
{
	int dig_count = 0, idx;
	long num = n;
	char *str;

	/* Count the digits of n*/
	do {
		dig_count++;
		num /= 10;
	} while (num != 0);

	/* Allocate space for all digits + null byte*/
	str = malloc(dig_count + 1);
	if (!str)
		return (NULL);
	/*Fill the string strating from the last character*/
	idx = dig_count - 1;
	do {
		str[idx] = '0' + (n % 10);
		n /= 10;
		idx--;
	} while (n != 0);
	str[dig_count] = '\0';

	return (str);

}
/**
 * _getenv - gets the environment variable's value
 * @var: the required variable
 *
 * Return: a pointer to the @var's value, NULL on failure.
 **/
char *_getenv(char *var)
{
	char *piece;
	int i;

	if (!*var)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		piece = _strtok(environ[i], "=");
		while (piece)
		{
			if (_strcmp(piece, var) == 0)
				return (environ[i]);
			piece = _strtok(NULL, "=");
		}
	}

	return (environ[i]);
}

/**
 * link_path - builds a linked list of the PATH directories.
 *
 * Return: a pointer to the head of the linked list, NULL on failure.
 **/
node_t *link_path(void)
{
	char *path, *piece;
	node_t *head = NULL;

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	piece = _strtok(path, ":");
	while (piece)
	{
		if (new_node(&head, piece) == NULL)
			return (NULL);
		piece = _strtok(NULL, ":");
	}

	return (head);
}

/**
 * new_node - adds a new node to the end of a linked list
 * @head: the head of the linked list.
 * @value: the value
 *
 * Return: pointer to the new_node, NULL on failure
 **/
node_t *new_node(node_t **head, char *value)
{
	node_t *new_node, *start = *head;

	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	new_node->value = value;

	if (start == NULL)
	{
		new_node->next = start;
		*head = new_node;
		return (*head);
	}
	else
	{
		node_t *tmp = start;

		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}

	return (new_node);
}

/**
 * free_list - frees a node_s list.
 * @head: the list_t's head.
 **/
void free_list(node_t *head)
{
	node_t *temp;

	if (head == NULL)
	{
		free(head);
		return;
	}
	while (head->next != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
	free(head->value);
	free(head);
}
