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
	int pid;
	char *path;

	printf("pathname: %s\n", pathname);
	if (!*pathname)
		return (-1);
	printf("pathname: %s\n", pathname);

	path = _strdup(pathname);
	if (!path)
		return (-1);
	printf("pathname: %s\n", path);
	if (search_path(&path) == -1)
		return (-1);
	printf("pathname: %s\n", pathname);

	printf("before fork: %s\n", path);
	fflush(stdout);
	pid = fork();

	if (pid == 0)
		execve(path, av, env);

	printf("after fork: %s\n", path);
	fflush(stdout);

	wait(NULL);
	free(path);
	return (pid);
}
