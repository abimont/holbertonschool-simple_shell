#include "shell.h"
/**
 * main - command interpreter
 * @argc: unused
 * @argv: arguments
 * Return: 0
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *line = NULL;
	size_t buf_size = 0;
	ssize_t characters = 0;

	name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* if a fd is associated with terminal */
			write(1, "< x_x > ", 8); /* write to standard output */

		characters = getline(&line, &buf_size, stdin);

		if (line[characters - 1]  == '\n') /* when '\n', write '\0' */
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
