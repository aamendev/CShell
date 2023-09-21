#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <unistd.h>
/**
 * readLine - reads line.
 *
 * Return: a string representing entered line.
 */
char *readLine()
{
	char *line = NULL;
	size_t size = 0;

	if (getline(&line, &size, stdin) == -1)
	{
		if (feof(stdin))
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	removeTrails(line);
	return (line);
}

