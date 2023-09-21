#ifndef MAIN_H
#define MAIN_H
char **splitString(char *av, char *separators);
char **splitStringDefault(char *av);
int findFile(char *file, char *path);
int findFileDefault(char *file);
int isInPath(char *file);
char *getLastFile(char *fullPath);
char *findFileInPath(char *file);
char **_strtok(char *);
int isInArray(char, char *);
char *removeTrails(char *);
char *readLine();
void _free(char **arr);
void loop(int status, char **argv, char **environ);
int executeCommands(int status, char **commands, char **argv, char **environ, int lineCount);
char *customGetLine();
int handlePath(int status, char *temp, char **commands, char **environ);
int isInWords(char *word, char **words);
int checkNumeric(char *input);
int handleBuiltIns(int status, int lines, char **argv, char **commands, char **environ);
#endif
