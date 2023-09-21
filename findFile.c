#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

#define PATH_SIZE 1024
#define MAX_TOKENS 100
/**
 * findFile - a function to find the files
 * @file: the file
 * @path: path of file
 *
 * Return: -1 on failure, 0 if fine not found, 1 otherwise
 */
int findFile(char *file, char *path)
{
	char *fullPath;
	struct stat st;

	fullPath = calloc(PATH_SIZE, sizeof(char));
	if (fullPath == NULL)
		return (-1);

	if (path[0] != '/')
		strcat(fullPath, "/");
	strcat(fullPath, path);
	strcat(fullPath, "/");
	strcat(fullPath, (file));
	if (stat(fullPath, &st) == 0)
	{
		free(fullPath);
		return (1);
	}
	free(fullPath);
	return (0);
}
/**
 * findFileDefault - default way of finding file (without path)
 * @file: the file
 *
 * Return: a call to main fineFile with empty path
 */
int findFileDefault(char *file)
{
	return (findFile(file, ""));
}
/**
 * getLastFile - gets the filename from path
 * @fullPath: full path
 *
 * Return: the filename or NULL
 */
char *getLastFile(char *fullPath)
{
	char **currentPath;
	char *finalPath;
	int i;

	i = 0;
	currentPath = splitString(fullPath, "/");
	if (currentPath == NULL)
		return (NULL);
	while (currentPath[i++] != NULL)
		;
	finalPath = strdup(currentPath[i - 2]);
	if (finalPath == NULL)
	{
		_free(currentPath);
		return (NULL);
	}
	i = 0;
	_free(currentPath);
	return (finalPath);
}
/**
 * isInPath - checks if file is in PATH
 * @file: filename
 *
 * Return: -1 on failure, 0 if not found, 1 otherwise
 */
int isInPath(char *file)
{
	char *pathEnv;
	char *filePathCopy;
	char **tokens;
	int i;
	int success;

	pathEnv = getenv("PATH");
	if (pathEnv == NULL)
		return (-1);
	filePathCopy = strdup(pathEnv);
	if (filePathCopy == NULL)
		return (-1);

	i = 0;
	success = 0;
	tokens = splitString(filePathCopy, ":");
	free(filePathCopy);

	if (tokens == NULL)
		return (-1);

	while (tokens[i] != NULL && success == 0)
	{
		success = findFile(file, tokens[i++]);
	}
	_free(tokens);
	return (success);
}
/**
 * findFileInPath - finds file in PATH
 * @file: file
 *
 * Return: filename or NULL
 */
char *findFileInPath(char *file)
{
	char *pathEnv;
	char *filePathCopy;
	char **tokens;
	int i;
	int success;
	int size = 0;

	pathEnv = getenv("PATH");
	filePathCopy = strdup(pathEnv);
	if (filePathCopy == NULL)
		return (NULL);
	i = 0;
	success = 0;
	success = findFileDefault(file);

	if (success)
	{
		free(filePathCopy);
		return (file);
	}
	tokens = splitString(filePathCopy, ":");
	if (tokens == NULL)
	{
		free(filePathCopy);
		return (NULL);
	}
	while (tokens[i] != NULL && success == 0)
		success = findFile(file, tokens[i++]);
	if (success)
	{
		free(filePathCopy);
		filePathCopy = strdup(tokens[i - 1]);
		size = sizeof(filePathCopy) + sizeof(file) + 2;
		filePathCopy = realloc(filePathCopy, size);
		strcat(filePathCopy, "/");
		strcat(filePathCopy, file);
	}
	_free(tokens);

	return (filePathCopy);
}
