#include "shell.h"

/**
 * command_path -
 * @cmd:
 *
 * Return:
 */

char *command_path(char *cmd)
{
        int index;
	char *path;
	char *tokens;
	char *path_array[100];
	char *new_path = NULL;
	struct stat buf;

	index = 0;
	path = strdup(_getenv("PATH")); /* gets a dup of PATH */
	tokens = strtok(path, ":"); /* split the path in a set of tokens */

	new_path = malloc(sizeof(char) * 100);
	if (_getenv("PATH")[0] == ':') 
	  if (stat(cmd, &buf) == 0) /* in case of success */
	    return (strdup(cmd)); /* return a copy of command */


	while (tokens != NULL)
	{
		path_array[index] = tokens; /* store results of tokens in path_array */
		index++;
		tokens = strtok(NULL, ":");
	}
	path_array[index] = NULL;


	/**
	 * copy tokens to new path
	 * add "/" and command 
	 * Example: after loop command will be /bin/ls
	 */ 
	for (index = 0; path_array[index]; index++)
	{
		strcpy(new_path, path_array[index]);
		strcat(new_path, "/");
		strcat(new_path, cmd);
		strcat(new_path, "\0");

		/* in case of sucess free resources and return new_path */
		if (stat(new_path, &buf) == 0)
		{
			free(path);
			return (new_path);
		}
		else 
			new_path[0] = 0;
	}
	free(path);
	free(new_path);
	
	/* After PATH checked and cmd is there locally */
	if (stat(cmd, &buf) == 0)
		return (strdup(cmd));

	/* in case of possible errors */ 
	return (NULL);
}

/**
 * display all the variables in the environment system
 *
 * Return: void
 */

int _printenv(void)
{
        char *str = environ[0];
        int index = 0, file_descr = 1;

        while (str[index] != '\0')
        {
                write(file_descr, str, strlen(str));
                write(file_descr, "\n", 1);
                str = environ[index]; /*++i without next line */
                ++index;
        }

	return (0);
}

/**
 * _getenv - gets the environment variables
 * @name:
 *
 * Return:
 */

char *_getenv(char *name)
{
        int index = 0;
        int len_name = strlen(name);

        for (index = 0; environ[index] != NULL; index++)
                if (strncmp(environ[index], name, strlen(name)) == 0)
                        return (&environ[index][len_name]);

        return (NULL);
}
