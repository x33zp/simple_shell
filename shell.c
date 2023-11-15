#include "shell.h"

/**
 * main - entery point of the shell.
 *
 * @argc: the argument count.
 * @argv: the argument vector.
 * @env: the enviroment variables.
 *
 * Return: 1 in  success.
*/
int main(int argc, char *argv[], char *env[])
{
	char *cmd = NULL, *prompt, **phrased_cmd = NULL, current_dir[1024];
	int status = 0;

	getcwd(current_dir, 1024), (void)argv, (void)argc, (void)env;
	prompt = (isatty(STDIN_FILENO) == 1) ? ("$ ") : ("");
	while (true)
	{
		signal(SIGINT, ctrl_c);
		cmd = utils_getline(prompt);
		if (cmd == NULL)
			free(cmd), exit(status);
		if (cmd[0] == '\n')
		{
			free(cmd);
			continue;
		}
		phrased_cmd = process_cmd(cmd);
		if (phrased_cmd[0][0] == '/')
		{
			if (find_command(phrased_cmd[0]))
				execute(phrased_cmd, argv[0]);
		}
		else
		{
			if (phrased_cmd[0][0] == '.' && phrased_cmd[0][1] == '/')
			{
				phrased_cmd[0] = concat_to_current(phrased_cmd[0], current_dir);
				if (find_command(phrased_cmd[0]))
					status = execute(phrased_cmd, argv[0]);
				getcwd(current_dir, 1024);
			}
			else if (_strcmp(phrased_cmd[0], "exit"))
				free(cmd), exit_fun(phrased_cmd, argv[0], &status);
			else if (!find_path(phrased_cmd, argv[0], &status))
				_print(STDERR_FILENO, "%s: 1: %s: not found\n", argv[0], phrased_cmd[0]);
		}
		free(phrased_cmd), free(cmd);
	}
	return (status);
}

/**
 * utils_getline - is the tool that is used to getline.
 *
 * @prompt: the prompt displayed to get the line.
 *
 * Return: pointer to the line read.
*/
char *utils_getline(char *prompt)
{
	size_t len = 0;
	ssize_t total_read;
	char *command = NULL;

	if (prompt[0])
		_print(STDOUT_FILENO, "%s", prompt);
	total_read = getline(&command, &len, stdin);
	if (total_read == -1)
	{
		free(command);
		exit(0);
	}
	command[total_read - 1] = '\0';
	if (command[0] == '\0')
	{
		command[0] = '\n';
		return (command);
	}
	command = remove_delim(command);
	return (command);
}

/**
 * ctrl_c - it is used to print newline and continue.
 *
 * @n: an argument to the ctrl-c.
 *
 * Return: void.
 */
void ctrl_c(int n)
{
	(void)n;
	_print(STDOUT_FILENO, "\n$ ");
}

/**
 * find_command - desides if the command is found in the spexified path.
 *
 * @path: is the sspecified path.
 *
 * Return: the accesablity or non accesibility.
*/
int find_command(char *path)
{
	if (!access(path, F_OK))
		return (1);
	return (0);
}

/**
 * exit_fun - the function that exits the progra.
 *
 * @ptr: is the pointer to pointer.
 * @prog_name: is the program name of the shell.
 * @status: the value that stores the exit status.
 *
 * Return: void.
 */
void exit_fun(char **ptr, char *prog_name, int *status)
{
	if (ptr[1] != NULL)
	{
		*status = extract_int(ptr[1]);

		if (*status == -1)
		{
			free(ptr);
			_print(STDERR_FILENO, "%s: 1: exit: Illegal number: %s\n",
												prog_name, ptr[1]);
			return;
		}
		else
			free(ptr), exit(*status);
	}
	else
		free(ptr);
	exit(*status);
}
