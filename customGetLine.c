#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#define BUFFER 1024
/**
 * customGetLine - custom version of the getline function
 *
 * Return: returns a string of the input
 */
char *customGetLine()
{
	int bufSize = BUFFER;
	int position = 0;
	char *buffer;
	int c;

	buffer = malloc(sizeof(char) * bufSize);
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		c = getchar();

		if (c == '\n' || c == EOF)
		{
			if (position == 0)
			{
				free(buffer);
				if (c == EOF)
					return ("\0");
				return (NULL);
			}
			buffer[position] = '\0';
			removeTrails(buffer);
			return (buffer);
		}
		if (c == '#' && position == 0)
		{
			return ("\0");
		}
		buffer[position] = c;
		position++;
		if (position >= bufSize)
		{
			bufSize *= 2;
			buffer = realloc(buffer, bufSize);
			if (buffer == NULL)
				return (NULL);
		}
	}
}

