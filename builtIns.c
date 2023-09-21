#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <ctype.h>
#define PATH_MAX 1024
/**
 * customExit - exits the shell
 * @commands: list of commands starting with exit
 * @lines: number of lines passed till now
 * @argv: original arg list
 * @status: current status.
 *
 * Return: exit status, 0 if non specified
 */
int customExit(int status, char **commands, int lines, char **argv)
{
	char *printString = "%s: %d: %s: Illegal number: %s\n";
	int newStatus;

	if (commands[1] == NULL)
	{
		_free(commands);
		if (lines == 1)
			status = 0;
		exit(status);
	}
	if (checkNumeric(commands[1]))
	{
		newStatus = atoi(commands[1]);
		_free(commands);
		exit(newStatus);
	}
	fprintf(stderr, printString, argv[0], lines++, commands[0], commands[1]);
	exit(2);
	return (2);
}
/**
 * customCd - builtin cd function
 * @status: current status.
 * @commands: list of commands.
 * @lines: number of lines.
 * @argv: originial arg list.
 *
 * Return: 1 on success, 0 otherwise.
 */
int customCd(int status, char **commands, int lines, char **argv)
{
	char *env;
	char *printString;

	printString = "%s: %d: %s: can't cd to %s\n";

	if (commands[1] == NULL)
	{
		env = getenv("HOME");
		chdir(env);
	}
	else if (!strcmp(commands[1], "-"))
	{
		env = getenv("OLDPWD");
		if (env != NULL)
		{
			printf("%s\n", env);
			chdir(env);
		}
		setenv("OLDPWD", "PWD", 1);
		setenv("PWD", env, 1);
	}
	else
	{
		status = chdir(commands[1]);
		if (status != 0)
			fprintf(stderr, printString, argv[0], lines++, commands[0], commands[1]);

	}
	return (EXIT_FAILURE);
}
/**
 * customEnv - builtin env function
 * @env: environ.
 *
 * Return: 1 on success, 0 otherwise.
 */
int customEnv(char **env)
{
	int i = 0;

	if (env == NULL)
		return (1);
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	return (0);
}
/**
 * handleBuiltIns - handles which builtin to call.
 * @lines: number of lines
 * @argv: original arg list.
 * @commands: the commands list.
 * @status: current status.
 * @environ: environ.
 *
 * Return: 0 on failure, or delegates call to other funcs.
 */
int handleBuiltIns(int status, int lines, char **argv, char **commands,
char **environ)
{
	if (!strcmp(commands[0], "exit"))
		return (customExit(status, commands, lines, argv));
	else if (!strcmp(commands[0], "cd"))
		return (customCd(status, commands, lines, argv));
	else
		return (customEnv(environ));
}
