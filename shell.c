#include "shell.h"
/**
 * main - entry ponint to the shell program.
 * @argc: the length of @av
 * @argv: the list of arguments passed to the program
 * @env: the environment information
 *
 * Return: 0 on success, error code on failure.
 **/
int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv,
		 char **env)
{
	char **av, *buff = NULL, *path, *piece;
	int i, in_len;
	int prompCount = 1;
	size_t n;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);
/* read input and put it in av */
		if (getline(&buff, &n, stdin) == -1)
		{   write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
/* get the length of the input */
		piece = _strtok(buff, " \n");
		in_len = 0;
		while (piece)
		{   in_len++;
			piece = _strtok(NULL, " \n");
		}
/* fill av */
		av = malloc(sizeof(av) * (in_len + 1));
		if (in_len > 0)
		{   piece = _strtok(buff, " \n");
			for (i = 0; piece; i++)
			{   av[i] = piece;
				piece = _strtok(NULL, " \n");
			}
			av[i] = NULL;
			path = av[0];

			if (execute(path, av, env) == -1)
				error(argv[0], prompCount, path, "exec");
		}
		if (isatty(STDIN_FILENO) != 1)
			break;
		prompCount++;
	}
	return (0);
}
