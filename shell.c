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
	char **av, *buff = NULL;
	int prompCount = 1;
	size_t n;

	while (1)
	{
		av = NULL, buff = NULL;
		n = 0;

		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);

		if (getline(&buff, &n, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		av = _strtok(buff, " \n", av);
		printf("after: %p\n", (void *)av);

		if (av)
		{
			if (execute(av[0], av, env) == -1)
				error(argv[0], prompCount, av[0], "exec");
		}

		free(av);
		free(buff);
		if (isatty(STDIN_FILENO) != 1)
			break;

		prompCount++;
	}
	return (0);
}
