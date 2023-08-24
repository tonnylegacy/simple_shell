#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point of the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ "); /* Display prompt */
		read = getline(&line, &len, stdin); /* Read user input */

		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n"); /* Ctrl+D pressed, exit gracefully */
				break;
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}

		/* Remove newline character from input */
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

		/* Create child process */
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execve(line, NULL, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			wait(NULL); /* Wait for child process to finish */
		}
	}

	free(line);
	return (0);
}
