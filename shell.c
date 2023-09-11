#include "shell.h"
/**
 * main - entry ponint to the shell program.
 * @argc: the length of @av
 * @argv: the list of arguments passed to the program
 * @env: the environment information
 *
 * Return: 0 on success, error code on failure.
 **/
int main(int argc, char **argv, char **env)
{
	char **av, *buff, *path, *piece;
	int i, in_len;
	size_t n;

	if (argc > 1)
	{   path = argv[1];
		if (execute(path, argv, env) == -1)
			perror("not found"); /* todo: handle errors */
	}
	else
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);
/* read input and put it in av */
		if (getline(&buff, &n, stdin) == -1)
			perror("getline");
/* get the length of the input */
		piece = strtok(buff, " \n");
		for (in_len = 0; piece; in_len++, piece = strtok(NULL, " \n"))
			;
/* fill av */
		av = malloc(sizeof(av) * (in_len + 1));
		if (in_len > 0)
		{   piece = strtok(buff, " \n");
			for (i = 0; piece; i++, piece = strtok(NULL, " \n"))
				av[i] = piece;
			av[i] = NULL;

			path = av[0];
			if (execute(path, av, env) == -1)
				perror("not found"); /* todo: handle errors */
		}
	}

	if (isatty(STDIN_FILENO) == 1)
	{
		if (execve(argv[0], argv, env) == -1)
			perror(argv[0]);
	}
	return (0);
}
