#include <ctype.h>
#include <string.h>
/**
 * checkNumeric - checks if a value is int.
 * @input: string rep of the input;
 *
 * Return: 1 if int, 0 otherwise
 */
int checkNumeric(char *input)
{
	int size = strlen(input);
	int i = 0;
	char c;

	while (i < size)
	{
		c = input[i++];
		if (!isdigit(c))
			return (0);
	}
	return (1);
}
