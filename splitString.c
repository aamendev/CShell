#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#define MAXARGS 1024
#define MAXLENGTH 1024
/**
 * _freeN - frees an array of n elements
 * @n: Number of elements
 * @arr: array
 */
void _freeN(int n, char **arr)
{
	int i = 0;

	for (i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}
/**
 * freeArrAndArg - frees array and arg list
 * @arr: array
 * @n: number of args
 * @arg: array of args
 */
void freeArrAndArg(char *arr, int n, char **arg)
{
	free(arr);
	_freeN(n, arg);
}
/**
 * splitString - Separates a string to words
 * @av: the string
 * @seps: separator between words
 *
 * Return: array of the separate words
 */
char **splitString(char *av, char *seps)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char *word;
	char **words;

	word = malloc(sizeof(char));
	words = malloc(MAXARGS * sizeof(char *));
	while (1)
	{
		if (av[i] == '#' && i > 0)
			break;
		word = realloc(word, (i + 1) * sizeof(char));
		if ((isInArray(av[i], seps) && ((i > 0) && !isInArray(av[i - 1], seps)))
		 || (av[i] == '\0'))
		{
			word[k] = '\0';
			words[j] = malloc(MAXLENGTH * sizeof(char));
			if (words[j] == NULL)
			{
				freeArrAndArg(word, j, words);
				return (NULL);
			}
			strcpy(words[j++], word);
			k = 0;
			if (av[i] == '\0')
				break;
		}
		else
			if (!isInArray(av[i], seps))
				word[k++] = av[i];
		i++;
	}
	free(word);
	words[j] = NULL;
	return (words);
}
/**
 * splitStringDefault - default string separator
 * @av: string to be separated
 *
 * Return: calls the main separation functino with ' ' as separator
 */
char **splitStringDefault(char *av)
{
	return (splitString(strdup(av), " \t\n"));
}

