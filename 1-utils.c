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

        // Calculate the length of the message
        int message_len = _strlen(mav) + _strlen(countStr) + _strlen(cav) + 10;

        // Allocate enough space for the message
        message = malloc(message_len);
        if (message == NULL) {
            // Handle error
            return;
        }

        // Build the message
        _strcpy(message, mav);
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

        // Free the allocated memory
        free(message);
        free(countStr);
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
        for(i = 0; i < new_size; i++)
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
                dest[i] = _strdup(piece); // Duplicate each piece
                piece = strtok(NULL, delim);
                i++;
        }
        dest[i] = NULL;
  
        free(buffdup); // Free the duplicated buffer
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
