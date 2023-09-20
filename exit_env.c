#include "shell.h"

/**
 * print_env - function prints the environemnt
 * @buff: the buffer containing commands.
 *
 * Return: 1 if there was env and it got printed, -1 if not.
 */
int print_env(char *buff)
{
	char **enva, **av;
	int i;

	av = prep_command(buff);
	if (!av)
		return (-1);

	if (_strcmp(av[0], "env") == 0)
	{
		for (enva = environ; *enva != NULL; ++enva)
		{
			write(1, *enva, _strlen(*enva));
			write(1, "\n", 1);
		}
		i = 0;
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
		return (1);
	}
	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
	return (-1);
}
/**
 * check_exit - function checks if exit is typed
 * @state:the struct containing the exit state
 * @av: list of args.
 *
 * Return: -1 on failure, nothing on succeed.
 */
int check_exit(char *av, ShellState *state)
{
	char *piece, *avdup;
	int i;

	avdup = _strdup(av);
	if (!avdup)
		return (-1);
	piece = strtok(avdup, " \n");
	if (_strcmp(piece, "exit") == 0)
	{
		state->should_exit = 1;

		piece = strtok(NULL, " \n");
		if (piece != NULL)
		{
			int status;
			/* check if the argument passed to exit isn't containing char */
			i = 0;
			while (piece[i] != '\0')
			{
				if (piece[i] < '0' || piece[i] > '9')
				{
					state->exit_status = 2;
					free(avdup);
					return (-1);
				}
				i++;
			}
			status = atoi(piece);
			if (status >= 0 && status <= 255)
				state->exit_status = status;
			else if (status > 255)
				state->exit_status = status % 256;
		}
	}
	free(avdup);
	return (0);
}


/**
 * check_dollar - function checks if the dollar argument $? is typed
 * to print the last exit state
 * @av: arguments passed to the function
 * @state: struct passed to the function containing the exit status
 */
void check_dollar(char *av, ShellState *state)
{
	char buffer[20];
	char *word = NULL;
	char *av_copy = strdup(av);

	if (av_copy != NULL)
	{
		word = strtok(av_copy, " \n");
		if (_strcmp(word, "$?") == 0)
		{
			int_to_str(state->exit_status, buffer);
			write(1, "Exit status: ", 13);
			write(1, buffer, _strlen(buffer));
			write(1, "\n", 1);
		}
		free(av_copy);
	}
}
/**
 * replace_dollar - function replaces dollar sigh with exit
 * @av: the input recieved
 * @state: the exit state
 */

void replace_dollar(char *av, ShellState *state)
{
	char buffer[20], *new_av;
	char *p = av;

	/* find $? in av */
	while (*p != '\0')
	{
		if (*p == '$' && *(p + 1) == '?')
		{
			break;
		}
		p++;
	}

	if (*p != '\0')
	{
		int_to_str(state->exit_status, buffer);
		*p = '\0';

		/* create a new string that is av + buffer + the rest of av after $? */
		new_av = malloc(_strlen(av) + _strlen(buffer) + _strlen(p + 2)
							  + 1);
		if (new_av == NULL)
		{
			/* handle error */
			return;
		}

		_strcpy(new_av, av);
		_strcat(new_av, buffer);
		_strcat(new_av, p + 2);

		_strcpy(av, new_av);

		free(new_av);
	}
}
