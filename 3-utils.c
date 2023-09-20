#include "shell.h"

/**
 * exit_err - prints the exit message when the exit argument is illegul.
 * @mav: the name of the program
 * @countStr: the number of prompts till now.
 * @cav: the arguments passed to the command
 **/
void exit_err(char **mav, char *countStr, char **cav)
{
	char *exit = _strdup("exit: Illegal number: "), *message;
	int message_len;

	if (!exit)
	{
		free(countStr);
		return;
	}
	message_len = _strlen(*mav) + _strlen(countStr) + _strlen(exit) +
		_strlen(cav[1]) + 5;
	message = malloc(message_len);
	if (message == NULL)
	{
		free(countStr);
		free(exit);
		return;
	}
	_strcpy(message, *mav);
	_strcat(message, ": ");
	_strcat(message, countStr);
	_strcat(message, ": ");
	_strcat(message, exit);
	_strcat(message, cav[1]);
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);

	free(message);
	free(countStr);
	free(exit);
}

/**
 * exec_err - prints the message when the command doesn't exist.
 * @mav: the name of the program
 * @countStr: the number of prompts till now.
 * @cav: the arguments passed to the command
 **/
void exec_err(char **mav, char *countStr, char **cav)
{
	char *message;
	int message_len;

	message_len = _strlen(*mav) + _strlen(countStr) + _strlen(*cav) + 10;
	message = malloc(message_len);
	if (message == NULL)
		return;
	_strcpy(message, *mav);
	_strcat(message, ": ");
	_strcat(message, countStr);
	_strcat(message, ": ");
	_strcat(message, *cav);

	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, ": not found\n", 12);
	free(message);
	free(countStr);
}


/**
 * freecav - frees command argv
 * @cav: the list
 * @frombuff: it'll only free if this is 1
 **/
void freecav(char **cav, int frombuff)
{
	int i = 0;

	if (frombuff == 1)
	{
		i = 0;
		while (cav[i])
		{
			free(cav[i]);
			i++;
		}
		free(cav);
	}
}

/**
 * init - tbh it's just for making less than 40 lines in the main function
 * @buff: the buffer
 * @atty: the atty status
 * @n: the getline size
 *
 * Return: the return value of getline function.
 **/
int init(char **buff, int *atty, size_t n)
{
	int stat = 0;

	if (isatty(STDIN_FILENO) == 1)
	{   *atty = 1;
		write(STDOUT_FILENO, "$ ", 2);
	}

	stat = getline(buff, &n, stdin);

	return (stat);
}
