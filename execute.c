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

	if (!*pathname)
		return (-1);

	if (search_path(&pathname) == -1)
		return (-1);

	pid = fork();
	if (pid == 0)
	{
		if (execve(pathname, av, env) == -1)
		{
			perror("");
			return (-1);
		}
	}

	wait(NULL);
	return (pid);
}
