#include "shell.h"

/**
 * execute_commands - this sends commands to get executed.
 * @commands: the commands
 * @env: the environment
 * @argv: the arguments passed
 * @promptNo: the number of prompts till now.
 *
 * Return: the exit status on failure, 0 on succeed.
 **/
int execute_commands(char ***commands, char **env, char **argv,
					 size_t promptNo)
{
	int i = 0;

	while (commands[i])
	{
		if (execute(commands[i][0], commands[i], env) == -1)
			return (error(argv, promptNo, commands[i], NULL, "exec"));
		i++;
	}

	return (0);
}

/**
 * execute_single_command - executes a command.
 * @av: the list of args
 * @env: the environment
 * @argv: the arguments passed to the main program
 * @promptNo: the number of prompts till now.
 * Return: the exit status on failure, 0 on succeed.
 **/
int execute_single_command(char **av, char **env, char **argv,
							size_t promptNo)
{
	if (execute(av[0], av, env) == -1)
	{
		return (error(argv, promptNo, av, NULL, "exec"));
	}
	return (0);
}

/**
 * handle_input - handles the input, prepares it for the execution.
 * @buff: the buffer containing the input.
 * @av: the args passed to the nuew program.
 * @commands: the commands
 * @env: the environment.
 * @argv: the arguments passed to the main program
 * @promptNo: the number of prompts till now.
 *
 * Return: the exit status.
 **/
int handle_input(char *buff, char **av, char ***commands, char **env,
				  char **argv, size_t promptNo)
{
	int nofcommands, i, ac, back;

	/* Initialize av and commands to NULL */
	av = NULL;
	commands = NULL;

	/* getting the number of commands separated by newline */
	nofcommands = noftokens(buff, "\n");

	if (nofcommands < 1)
		return (-1);
	else if (nofcommands == 1)
		av = prep_command(buff);
	else
		commands = prep_commands(buff, nofcommands);

	/* the execution */
	if (commands)
	{
		back = execute_commands(commands, env, argv, promptNo);
		for (i = 0; i < nofcommands; i++)
			free(commands[i]);
		free(commands);
	}

	if (av)
	{
		ac = noftokens(buff, " \n");
		back = execute_single_command(av, env, argv, promptNo);
		for (i = 0; i < ac; i++)
			free(av[i]);
		free(av);
	}
	return (back);
}

/**
 * prep_command - prepares the received commans for the execution.
 * @buff: the buffer containing the commands.
 *
 * Return: the prepared command.
 **/
char **prep_command(char *buff)
{
	int ac;
	char **av;

	/* getting the number of arguments */
	ac = noftokens(buff, " \n");
	if (ac < 1)
		return (NULL);
	/* allocating memory for the tokens */
	av = malloc(sizeof(av) * (ac + 1));
	if (!av)
		return (NULL);

	/* filling the data */
	if (getokens(buff, av, " \n") == -1)
	{
		free(av);
		return (NULL);
	}

	return (av);
}

/**
 * prep_commands - prepares the received commands for the execution.
 * @buff: the buffer containing the commands.
 * @nofcommands: the number of commands.
 *
 * Return: the prepared commands.
 **/
char ***prep_commands(char *buff, int nofcommands)
{
	char ***commands, **sub;
	int i;

	/* allocating memory for commands */
	commands = malloc(sizeof(*commands) * nofcommands);
	if (!commands)
		return (NULL);

	/* allocate memory for sub */
	sub = malloc(sizeof(*sub) * nofcommands);
	if (!sub)
	{
		free(commands);
		return (NULL);
	}

	/* separate commands */
	if (getokens(buff, sub, "\n") == -1)
	{
		free(commands);
		free(sub);
		return (NULL);
	}

	/* filling the data */
	i = 0;
	while (nofcommands)
	{
		getokens(sub[i], commands[i], " \n");
		i++, nofcommands--;
	}

	free(sub);
	return (commands);
}
