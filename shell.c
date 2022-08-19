#include "shell.h"
/**
 * main - command interpreter
 * @argc: unused
 * @argv: arguments
 * Return: 0
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *input = NULL;
	size_t size = 0;
	ssize_t characters = 0;

	name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* if a fd is a terminal */
			write(1, "x_x $ ", 7); /* write to standard output */

		characters = getline(&input, &size, stdin);
		if (characters == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}

		if (input[characters - 1]  == '\n') /* when '\n', write '\0' */
			input[characters - 1]  = '\0';
		if (*input == '\0')
			continue;
		if (command_read(input, characters) == 2) /* in case of exit */
			break;
		else 
			continue;
		}

	free(input);
	input = NULL;

	return (0);
}
