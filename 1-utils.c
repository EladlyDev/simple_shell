#include "shell.h"

/**
 * error - prints an error similar to sh
 * @mav: the first element in av for the main function, the program name.
 * @count:  the number of prompts till now.
 * @cav: the name of the command.
 * @src: where the error coming from.
 * @buff: the buffer cotaining the command.
 *
 * Return: the exit status depending on the kind of the error.
 **/
int error(char **mav, int count, char **cav, char *buff, char *src)
{
	char *countStr;

	countStr = itos(count);
	if (!cav && buff)
		cav = prep_command(buff);

	if (_strcmp(src, "exec") == 0)
	{
		exec_err(mav, countStr, cav);
		return (127);
	}
	else if (_strcmp(src, "exit") == 0)
	{
		exit_err(mav, countStr, cav);
		return (2);
	}
	else
		perror(*mav);

	free(countStr);
	return (2);
}

/**
  * _realloc -  reallocates a memory block using malloc and free.
  * @ptr: pointer to define its size
  * @old_size: the old size of the pointer
  * @new_size: the new size of the pointer
  *
  * Return: a pointer to the new memory filled with @ptr's data, NULL on fail.
***/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *ptv; /* a void pointer */
	char *char_ptv; /* a char pointer for initializing */
	unsigned int i;

    /* Edge cases. */
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		ptv = malloc(old_size + new_size);
		if (!ptv)
			return (NULL);
		return (ptv);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	/* Allocate memory. */
	ptv = malloc(new_size);
	if (ptv == NULL)
		return (NULL);

	/* Initialize ptv to zero */
	char_ptv = (char *)ptv;
	for (i = 0; i < new_size; i++)
		char_ptv[i] = 0;

	/* Filling the data. */
	new_size = new_size > old_size ? old_size : new_size;
	_strncpy(ptv, ptr, new_size);

	free(ptr);
	return (ptv);
}

/**
 * getokens - gets the tokens form a string, and puts them inside an arr.
 * @buff: the buffer containing the string.
 * @dest: the destination to put the tokens.
 * @delim: the delimiter between tokens.
 *
 * Return: 0 on success, -1 on failure.
 **/
int getokens(char *buff, char **dest, char *delim)
{
	char *piece, *buffdup;
	int i = 0;

	if (!buff || !dest || !delim)
		return (-1);

	/* duplicating the buffer */
	buffdup = _strdup(buff);
	if (!buffdup)
		return (-1);
	/* getting each piece and filling the data */
	piece = strtok(buffdup, delim);
	while (piece)
	{
		dest[i] = _strdup(piece);
		piece = strtok(NULL, delim);
		i++;
	}
	dest[i] = NULL;

	free(buffdup);
	return (0);
}

/**
 * noftokens - gets the number of  tokens in a string.
 * @buff: the buffer
 * @delim: the delimiters between each token.
 *
 * Return: the number of tokens.
 **/
int noftokens(char *buff, char *delim)
{
	int noftokens = 0;
	char *piece, *buffdup;

	if (!buff)
		return (0);
	if (!delim)
		return (1);
	/* duplicating the buff so we don't edit the original */
	buffdup = _strdup(buff);
	if (!buffdup)
		return (0);
	/* getting the tokens and counting them */
	piece = strtok(buffdup, delim);
	while (piece)
	{
		noftokens++;
		piece = strtok(NULL, delim);
	}
	free(buffdup);
	return (noftokens);
}

/**
 * handle_exit_status - handles the exit status.
 * @av: the list of args.
 **/
void handle_exit_status(char **av)
{
	write(1, "Exit status: ", 13);
	write(1, av[0], _strlen(av[0]));
	write(1, "\n", 1);
}
