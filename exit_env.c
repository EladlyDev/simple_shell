#include "shell.h"

/**
 * print_env - function prints the environemnt
 */
void print_env(char *av[])
{
	char **enva;

	if (_strcmp(av[0], "env") == 0) 
	{
		for (enva = environ; *enva != NULL; ++enva)
		{
			write(1, *enva, _strlen(*enva));
			write(1, "\n", 1);
		}
	}
}
/**
 * check_exit - function checks if exit is typed
 * @state:the struct containing the exit state
 */
void check_exit(char *av, ShellState *state) // av is a single string
{
    char buffer[20];
    char *word = NULL; // pointer to store the first word
    word = strtok(av, " \n"); // split av by spaces and newlines and get the first word
    if (_strcmp(word, "exit") == 0) // compare word with "exit"
    {
        state->should_exit = 1;

        word = strtok(NULL, " \n"); // get the next word
        if (word != NULL) // check if there is another word after "exit"
        {
            int status = atoi(word); // convert the word to an integer

            if (status >= 0 && status <= 255)
            {
                state->exit_status = status; // save the exit status in your ShellState struct
            }
        }
        else
            return;
    }
}


/*
 * check_dollar - function checks if the dollar argument $? is typed to print the last exit state
 * @args: arguments passed to the function
 * @state: struct passed to the function containing the exit status
 */
void check_dollar(char *av, ShellState *state) // av is a single string
{
    char buffer[20];
    char *word = NULL; // pointer to store the first word
    char *av_copy = strdup(av); // make a copy of av
    if (av_copy == NULL) {
        // handle error
    }
    word = strtok(av_copy, " \n"); // split av_copy by spaces and newlines and get the first word
    if (_strcmp(word, "$?") == 0) // compare word with "$?"
    {
        int_to_str(state->exit_status, buffer); // convert state->exit_status to string
        write(1, "Exit status: ", 13);
        write(1, buffer, _strlen(buffer));
        write(1, "\n", 1);
    }
    free(av_copy); // don't forget to free the copy when you're done with it
}
/**
 * replace_dollar : function replaces dollar sigh with exit
 * @av: the input recieved
 * @state: the exit state
 */

void replace_dollar(char *av, ShellState *state) // av is a single string
{
    char buffer[20];
    char *p = av; // pointer to iterate over av

    // find $? in av
    while (*p != '\0')
    {
        if (*p == '$' && *(p + 1) == '?')
        {
            break;
        }
        p++;
    }

    if (*p != '\0') // if $? was found
    {
        int_to_str(state->exit_status, buffer); // convert state->exit_status to string using int_to_str
        *p = '\0'; // terminate av at the position of $?
        
        // create a new string that is av + buffer + the rest of av after $?
        char *new_av = malloc(_strlen(av) + _strlen(buffer) + _strlen(p + 2) + 1);
        if (new_av == NULL)
        {
            // handle error
            return;
        }

        _strcpy(new_av, av); // copy av into new_av
        _strcat(new_av, buffer); // append buffer to new_av
        _strcat(new_av, p + 2); // append the rest of av after $? to new_av

        _strcpy(av, new_av); // copy new_av back into av

        free(new_av); // don't forget to free the new string when you're done with it
    }
}
