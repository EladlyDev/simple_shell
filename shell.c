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
	char *buff, ***commands, **av;
	size_t n, promptNo;
	int atty = -1, stat, noft;
	ShellState state;

	state.should_exit = state.exit_status = n = stat = noft = promptNo = 0;

	while (1)
	{   buff = NULL, n = 0, av = NULL, commands = NULL;
		promptNo++;
		if (isatty(STDIN_FILENO) == 1)
		{   atty = 1;
			write(STDOUT_FILENO, "$ ", 2);
		}
		stat = getline(&buff, &n, stdin);
		if (stat == -1)
		{   free(buff);
			if (atty == 1)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		noft = noftokens(buff, " \n");
		if (noft == 0 || noft == -1)
		{   free(buff);
			continue;
		}
		if (print_env(buff) == 1)
			continue;
		if (check_exit(buff, &state) == -1)
		{   state.exit_status = error(argv, promptNo, av, buff, "exit");
			free(buff);
			if (!atty)
				break;
			continue;
		}
		state.exit_status = handle_input(buff, av, commands, env, argv,
										 promptNo);
		free(buff);
	}
	return (state.exit_status);
}
