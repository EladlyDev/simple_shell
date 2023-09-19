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
/**
 * int_to_str - function converts int to string
 * @n: the number to convert
 * @buffer: the buffer containing the string
 */

void int_to_str(int n, char *buffer)
{
	int i = 0, j = 0, temp;
	char sign = '+';

	if (n == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return;
	}

	if (n < 0)
	{
		sign = '-';
		n = -n;
	}

	while (n > 0)
	{
		temp = n % 10;
		buffer[i++] = temp + '0';
		n /= 10;
	}

	if (sign == '-')
	{
		buffer[i++] = sign;
	}

	buffer[i] = '\0';

	i--;
	while (j < i)
	{
		temp = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = temp;
		j++;
		i--;
	}
}
