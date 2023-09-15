#include "shell.h"

/**
 * _strtok - takes a string, and breaks it down to tokens, each token ends with
 * a specified delim.
 * @str: the string
 * @delim: the delim/s
 * @arr: an arr to put the tokens in.
 *
 * Return: a new arr filled of tokens tokens, -1 on failure.
 **/
char** _strtok(char *str, char *delim, char **arr)
{
	char *token;
	static char *savePtr;
	static int index;
	int chain, wasDelim, isDelim, i, j;
	static size_t len;

	if (!savePtr)
		savePtr = str;

	if (!len)
	{
		len = noftokens(str, delim);
		if (len == 0)
			return (NULL);
	}
	token = savePtr;
	chain = wasDelim = isDelim = i = j = 0;

	if (savePtr)
	{
	while (savePtr[i])
	{
		while (delim[j])
		{
			if (savePtr[i] == delim[j])
			{   isDelim = 1;
				chain++;
				savePtr[i] = '\0';
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
	}
	if (!arr)
	{
		arr = malloc((sizeof(arr) * len) + 8);
		if (!arr)
			return (NULL);
		index = 0;
	}
	arr[index] = token;
	index++;

	if ((size_t)index < len)
	{
		_strtok(NULL, delim, arr);
	}
	arr[index] = NULL;
	len = 0;
	savePtr = NULL;
	return (arr);
}

size_t noftokens(char *str, char *delim)
{
	int i, j, isDelim, wasDelim, noftokens;

	if (!str)
		return (0);
	if (!delim)
		return (1);

	i = j = isDelim = wasDelim = noftokens = 0;
	while (str[i])
	{
		while (delim[j])
		{
			if (str[i] == delim[j])
			{   isDelim = 1;
				break;
			}
			j++;
		}
		if (isDelim == 1)
			wasDelim = 1;
		if (isDelim == 0 && wasDelim == 1)
		{   noftokens++;
			wasDelim = 0;
		}
		if (!str[i + 1])
		{noftokens++;
			break;
		}

		i++, isDelim = j = 0;
	}

	return (noftokens);
}
