#include "shell.h"
/**
 * main - entry ponint to the shell program.
 * @argc: the length of @av
 * @argv: the list of arguments passed to the program
 * @env: the environment information
 *
 * Return: 0 on success, error code on failure.
 **/
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	char **av, *buff = NULL, *buffdup, *path, *piece;
	int i, in_len;
	size_t n;

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);
/* read input and put it in av */
	if (getline(&buff, &n, stdin) == -1)
	{   write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
/* get the length of the input */
	buffdup = _strdup(buff);
	piece = strtok(buffdup, " \n");
	in_len = 0;
	while (piece)
	{   in_len++;
		piece = strtok(NULL, " \n");
	}
/* fill av */
	av = malloc(sizeof(av) * (in_len + 1));
	if (in_len > 0)
	{   piece = strtok(buff, " \n");
		for (i = 0; piece; i++)
		{   av[i] = piece;
			piece = strtok(NULL, " \n");
		}
		av[i] = NULL;
		path = av[0];
		if (execute(path, av, env) == -1)
			perror("not found"); /* todo: handle errors */
	}

	if (isatty(STDIN_FILENO) == 1)
	{
		if (execve(argv[0], argv, env) == -1)
			perror(argv[0]);
	}
	return (0);
}
