#include "shell.h"

/**
 * execute - the function that executes any of the command.
 *
 * @command: the command and its arguments.
 * @program_name: the name of the program at this instance.
 *
 * Return: 1 - in success, other in failure and errno is set.
*/
int execute(char **command, char *program_name)
{
	char *path = command[0];
	pid_t pid;
	int exit_status, exec_return = 0, st = 0;

	pid = fork();
	if (pid == -1)
	{
		_print(STDOUT_FILENO, "%s: ", program_name);
		perror("fork fails");
	}
	else if (pid == 0)
	{
		exec_return = execve(path, command, environ);
		if (exec_return == -1)
			exit(WEXITSTATUS(exec_return));
	}
	else
	{
		wait(&exit_status);
		if (WIFEXITED(exit_status))
			st = WEXITSTATUS(exit_status);
		if (st != 0)
			return (2);
		else
			return (0);
	}
	return (0);
}


/**
 * find_path - this is used to find the path of the command.
 *
 * @command: is the command list of the program.
 * @program_name: is the name of the progaram.
 * @exit_st: the exit satatus of the file.
 *
 * Return: 1 - if the command is found and 0 - if the command is not found.
*/
int find_path(char **command, char *program_name, int *exit_st)
{
	char *cmd = command[0];
	char arr[10][1024] = {
		"/usr/local/bin/", "/usr/local/bin/", "/usr/bin/", "/sbin/", "/susr/bin/",
		"/bin/", "/usr/games/", "/usr/local/games/", "/mnt/c/program/", "\0"};
	int caseo = 0;
	int i = 0, status = 0;

	while (arr[i][0] && !status)
	{
		caseo = find_command(_strconc(arr[i], cmd));
		if (caseo)
		{
			command[0] = arr[i];
			*exit_st = execute(command, program_name);
			status = FOUND;
			break;
		}
		unconcat(arr[i], cmd);
		i++;
	}

	if (!status)
		*exit_st = 127;
	return (status);
}
