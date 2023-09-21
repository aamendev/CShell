#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "main.h"

#define BUFFER 1000
/**
 * main - main function
 * @argc: number of arguments
 * @argv: list of arguments
 * @environ: environmnet
 *
 * Return: 0, always success
 */
int main(int argc, char **argv, char **environ)
{
	int status = 0;

	(void)argc;
	loop(status, argv, environ);
	return (status);
}
