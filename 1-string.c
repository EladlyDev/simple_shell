#include "shell.h"

/**
 * _strtok - takes a string, and breaks it down to tokens, each token ends with
 * a specified delim.
 * @str: the string
 * @delim: the delim/s
 *
 * Return: a pointer to the token, NULL if there are no more tokens
 **/
char *_strtok(char *str, char *delim)
{
	char *token;
	static char *savePtr;
	int chain, wasDelim, isDelim, i, j;

	if (!savePtr)
		savePtr = _strdup(str);
	token = savePtr;
	chain = wasDelim = isDelim = i = j = 0;
	if (!savePtr)
	{   free(savePtr);
		return (NULL);
	}
	while (savePtr[i])
	{
		while (delim[j])
		{
			if (savePtr[i] == delim[j])
			{   isDelim = 1;
				chain++;
				savePtr[i] = '\0';
				j = 0;
				break;
			}
			j++;
		}
		if (isDelim == 1)
			wasDelim = 1;
		if (isDelim == 0 && wasDelim == 1)
		{   savePtr = &savePtr[i + chain - 1];
			wasDelim = 0;
			break;
		}
		if (!savePtr[i + 1])
		{	savePtr = NULL;
			break;
		}
		i++, isDelim = j = 0;
	}

	return (token);
}

/**
 * _strncpy - This function copies a string,
 * it works exactly like strncpy function
 * @dest: the destination to copy to
 * @src: the source string
 * @n: the bytes number
 *
 * Return: pointer to the copied string
 */


char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}
