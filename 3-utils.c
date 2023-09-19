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
