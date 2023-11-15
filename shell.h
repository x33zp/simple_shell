#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

#define FOUND 1
int execute(char **, char *);
/*
 * The following are list of sting manipulation functions and other
 * tools that are used to print string and errors.
 */
char *unconcat(char *, char *);
char *_strconc(char *, char *);
void _print(int, const char *format, ...);
void _putchar(char, int);
void print_string(va_list, int);
void print_int(int, int);
char *utils_getline(char *);
int _strlen(char *);
int find_command(char *);
int _strcmp(char *, char *);
char *concat_to_current(char *instrction, char *cur_dir);
char **process_cmd(char *);
void ctrl_c(int n);
char *utils_getline(char *prompt);
int find_path(char **, char *, int *);
int extract_int(char *intger);
void exit_fun(char **ptr, char *prog_name, int *);
char *remove_delim(char *);
int cmp(char);

#endif

