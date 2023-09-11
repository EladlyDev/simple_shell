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
	node_t *head = NULL;
	char *path;
	struct stat buff;

	if (!*pathname || !**pathname)
		return (-1);

	/* if it is a path and exist */
	if (stat(*pathname, &buff) == 0)
		return (1);

	/* search in PATH */
	head = link_path();

	while (head != NULL)
	{
		path = _strdup(head->value);

		if (path[_strlen(path) - 1] != '/')
			strcat(path, "/");
		strcat(path, *pathname);

		if (stat(path, &buff) == 0)
		{
			*pathname = path;
			return (1);
		}

		head = head->next;
	}

	free(path);
	free(*pathname);
	return (-1);
}
