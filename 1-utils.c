#include "shell.h"

/**
 * error - prints an error similar to sh
 * @mav: the first element in av for the main function, the program name.
 * @count:  the number of prompts till now.
 * @cav: the name of the command.
 * @src: where the error coming from.
 **/
void error(char *mav, int count, char *cav, char *src)
{
	char *countStr, *message;

	countStr = itos(count);

	message = _strdup(mav);
	_strcat(message, ": ");
	_strcat(message, countStr);
	_strcat(message, ": ");
	_strcat(message, cav);

	if (_strcmp(src, "exec") == 0)
	{
		write(STDERR_FILENO, message, _strlen(message));
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else
		perror(message);
}
