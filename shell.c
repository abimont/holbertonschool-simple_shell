#include "shell.h"

/**
 * main - command interpreter
 *
 * Return:
 */

int main(int __attribute__((unused)) argc, char *argv[])
{
	char *line = NULL;
	size_t buf_size = 0;
	ssize_t characters = 0;

	name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* check if an open file descriptor is associated with terminal device */
			write(1, "< x_x > ", 8); /* write to standard output */

		characters = getline(&line, &buf_size, stdin); /* store number of characters read */

		if (line[characters - 1]  == '\n') /* when encountering new line, write null terminating byte */
			line[characters - 1]  = '\0';
		if (*line == '\0')
			continue;
		if (command_read(line, characters) == 2) /* in case of exit */ 
			break;
	}

	free(line);
	line = NULL;
	
	return (0);
}


int command_read(char *input, size_t __attribute__((unused))characters)
{
	char *token = NULL;
	char *cmd_arr[100];
	int index;

	if (strcmp(input, "exit") == 0)
		return (2);
	if (strcmp(input, "env") == 0)
		return (_printenv());
	token = strtok(input, " "), index = 0;
	while (token)
	{
		cmd_arr[index++] = token;
		token = strtok(NULL, " ");
	}
	cmd_arr[index] = NULL;

	return (execute(cmd_arr));
}

int execute(char *cmd_arr[])
{
	char *exe_path = NULL;
	char *cmd = NULL;
	pid_t pid;
	int status;

	cmd = cmd_arr[0];
	exe_path = command_path(cmd);
	if (exe_path == NULL)
	{
	        write(2, name, strlen(name));
		write (2, ": ", 2);
	        write(2, cmd, strlen(cmd));
		write(2, ": not found\n", 12);

		return (3);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error:");
		return (-1);
	}
	if (pid > 0)
		wait(&status);
	else if (pid == 0)
	{
	  if (environ)
	    {
		(execve(exe_path, cmd_arr, environ));
		perror("Error:");
		exit(1);
	    }
	  else
	    {
	      execve(exe_path, cmd_arr, NULL);
	    }
	}
	free(exe_path);
	return (0);
}
