#include <string.h>
/**
 * removeTrails - removes trailing white spaces
 * @str: string to remove from
 *
 * Return: modified String or NULL on failure
 */
void removeTrails(char *str)
{
	int i = 0;
	int index = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		if (str[i] != ' '  && str[i] != '\t' && str[i] != '\n')
			index = i;
		i++;
	}
	str[index + 1] = '\0';
}
