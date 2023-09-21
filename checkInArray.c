#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * isInArray - checks if a char is in an array
 * @c: the character to check
 * @arr: the array
 *
 * Return: 1 if in array, 0 otherwise
 */
int isInArray(char c, char *arr)
{
	size_t i = 0;
	size_t size;

	if (arr == NULL)
		return (0);
	size = strlen(arr);
	while (i < size)
		if (c == arr[i++])
			return (1);
	return (0);
}
/**
 * isInWords - checks if a word in in the given list
 * @word: the word to check for.
 * @words: words list to check in.
 *
 * Return: 1 if in array, 0 othwerise
 */
int isInWords(char *word, char **words)
{
	int i = 0;

	while (words[i] != NULL)
	{
		if (!strcmp(word, words[i++]))
			return (1);
	}
	return (0);
}
