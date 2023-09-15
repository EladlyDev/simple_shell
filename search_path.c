#include "shell.h"

/**
 * search_path - takes a pathname, and if it is a path it checks if it exists
 * if it's a name it try to find it in PATH
 * @pathname: a pointer to the pathname.
 *
 * Return: 1 if it exists, -1 if not.
 **/
int search_path(char **pathname)
{
	node_t *head = NULL, *tmp;
	char *path;
	struct stat buff;

	if (!*pathname || !**pathname)
		return (-1);

	/* if it is a path and exist */
	if (stat(*pathname, &buff) == 0)
		return (1);

	/* search in PATH */
	head = link_path();
	tmp = head;
	while (tmp != NULL)
	{
		path = _strdup(tmp->value);

		if (path[_strlen(path) - 1] != '/')
			_strcat(path, "/");
		_strcat(path, *pathname);

		if (stat(path, &buff) == 0)
		{
			free_list(head);
			*pathname = path;
			return (1);
		}

		tmp = tmp->next;
		free(path);
	}

	free_list(head);
	return (-1);
}
