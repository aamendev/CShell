#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "main.h"
/**
 * loop - main loop for shell
 * @argv: args from main
 * @environ: environ from main
 * @status: current status.
 *
 * Return: returns status
 */
void loop(int status, char **argv, char **environ)
{
	char *commandLine = NULL;
	char **commands = NULL;
	int lines = 1;

	do {
		if (isatty(STDIN_FILENO) != 0)
			printf("-> ");
		commandLine = customGetLine(status);
		if (commandLine != NULL && strcmp(commandLine, "\n"))
		{
			commands = splitString(commandLine, " \t\n");
			status = executeCommands(status, commands, argv, environ, lines);
			_free(commands);
		}
		free(commandLine);
		lines++;
	} while (1);
}
/**
 * executeCommands - executes shell commands
 * @commands: commands list
 * @argv: args form main
 * @environ: environmnet
 * @lines: number of lines
 * @status: current status of program
 *
 * Return: 1 on success, 0 otherwise
 */
int executeCommands(int status, char **commands, char **argv,
char **environ, int lines)
{
	char *temp = NULL;
	char *builtins[] = {"exit", "cd", "env", NULL};

	temp = getLastFile(commands[0]);
	if (temp[0] == '\0')
	{
		_free(commands);
		free(temp);
		exit(EXIT_SUCCESS);
	}
	if (temp == NULL)
		return (0);
	if (isInWords(temp, builtins))
	{
		free(temp);
		return (handleBuiltIns(status, lines, argv, commands, environ));
	}
	else if (isInPath(temp))
	{
		return (handlePath(status, temp, commands, environ));
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], lines, commands[0]);
		free(temp);
		return (127);
	}
	free(temp);
	return (2);
}
/**
 * handlePath - handlesPath args
 * @status: current status
 * @commands: commands list
 * @environ: handles environment
 * @temp: name of final file.
 *
 * Return: status
 */
int handlePath(int status, char *temp, char **commands,
char **environ)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		temp = findFileInPath(commands[0]);
		if (execve(temp, commands, environ) == -1)
		{
			perror("EXECVE");
			status = errno;
			printf("%d\n", errno);
		}
	free(temp);
	_free(commands);
	status = 0;
	}
	else if (pid < 0)
		perror("pid");
	else
		wait(&status);
	return (WEXITSTATUS(status));
}
/**
 * _free - frees an array
 * @arr: the array
 */
void _free(char **arr)
{
	int i = 0;

	if (arr == NULL)
		return;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}
