#include "shell.h"

/**
 * _strlen - This function returns the length of a string.
 * @s: the string.
 *
 * Return: the length of @s
 **/
int _strlen(char *s)
{
	int count;

	for (count = 0; s[count] != '\0'; count++)
		;

	return (count);
}

/**
  * _strdup - duplicates a string to a newly allocated memory
  * @str: the string to copy
  *
  * Return: a pointer to the new allocated memory, or NULL if it fails
***/

char *_strdup(char *str)
{
	int i;
	char *ptc;
	int str_len;

	if (!str)
		return (NULL);
	str_len = _strlen(str);
	ptc = malloc((sizeof(char) * str_len) + 1);
	if (!ptc)
		return (NULL);
	for (i = 0; i < str_len; i++)
	{
		ptc[i] = str[i];
	}
	ptc[i] = '\0';

	return (ptc);
}

/**
 * _strcmp - This function compares two strings,
 * work exactly like strcmp
 * @s1: string no 1
 * @s2: string no 2
 *
 * Return: 1 if s1 > s2, -1 if s1 < s2 and 0 if they are equals
 **/
int _strcmp(char *s1, char *s2)
{
	int i, end;
	int s1_len = _strlen(s1);
	int s2_len = _strlen(s2);

	if (s1_len > s2_len)
		end = s1_len;
	else
		end = s2_len;

	for (i = 0; i < end; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strcpy - A function that copies a string src
 * including the '\0' to the destination dest
 * @dest: the destination
 * @src: the source string
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int len = _strlen(src);
	int i;

	for (i = 0; i <= len; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strcat - This function concatenates two strings
 * @src: the source string
 * @dest: the destination
 *
 * Return: a pointer to the result
 **/
char *_strcat(char *dest, char *src)
{
	int dest_len = _strlen(dest);
	int src_len = _strlen(src);
	int i;

	for (i = 0; i < src_len; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + src_len] = '\0';
	return (dest);
}
