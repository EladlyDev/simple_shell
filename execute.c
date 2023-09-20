#include "shell.h"

/**
 * execute - takes the name/path of the file/command and executes it if it
 * exists, if not, it try to find it in PATH.
 * @pathname: the name/path of the file
 * @av: the list of arguments passed to the new process.
 * @env: the environment passed to the new process.
 *
 * Return: the pid of the new process, -1 on failure.
 **/
int execute(char *pathname, char **av, char **env)
{
	int pid, status;
	char *path;

	if (!*pathname)
		return (-1);

	path = _strdup(pathname);
	if (!path)
		return (-1);
	if (search_path(&path) == -1)
	{
		free(path);
		return (-1);
	}

	pid = fork();
	if (pid == 0)
		if (execve(path, av, env) == -1)
			_exit(EXIT_FAILURE);

	free(path);
	wait(&status);
	return (status);
}
