#include "shell.h"

void handle_exit_status(char **av)
{
    write(1, "Exit status: ", 13);
    write(1, av[0], _strlen(av[0]));
    write(1, "\n", 1);
}

void execute_commands(char ***commands, char **env, char **argv, size_t promptNo)
{
    int i = 0;
    while (commands[i])
    {
        if (execute(commands[i][0], commands[i], env) == -1)
        {
            error(argv[0], promptNo, commands[i][0], "exec");
            return; // use return instead of exit
        }
        i++;
    }
}

void execute_single_command(char **av, char **env, char **argv, size_t promptNo)
{
    if (execute(av[0], av, env) == -1)
    {
        error(argv[0], promptNo, av[0], "exec");
    }
}

void handle_input(char *buff, char **av, char ***commands, char **env, char **argv, size_t promptNo, ShellState *state)
{
    int nofcommands;
    int i;
    int ac;

    /* Initialize av and commands to NULL */
    av = NULL;
    commands = NULL;

    /* getting the number of commands separated by newline */
    nofcommands = noftokens(buff, "\n");

    if (nofcommands < 1)
        return;
    else if (nofcommands == 1)
    {   /* getting the number of arguments */
        ac = noftokens(buff, " \n");
        if (ac < 1)
            return;
        /* allocating memory for the tokens */
        av = malloc(sizeof(av) * (ac + 1));
        if (!av)
            return;

        /* filling the data */
        if (getokens(buff, av, " \n") == -1)
        {
            free(av); // free av before returning
            return;
        }
        /* check if command is exit status print request */
        if (av[0][0] == '0' && av[0][1] == '\0')
        {
            handle_exit_status(av);
            for(i=0; i<ac; i++)
                free(av[i]); // free each argument after using it
            free(av); // free av after using it
            return; // return after printing exit status
        }
    }
    else    /* if there are more than 1 command */
    {   /* allocating memory for commands */
        commands = malloc(sizeof(*commands) * nofcommands);
        if (!commands)
            return;

        /* allocate memory for sub */
        char **sub = malloc(sizeof(*sub) * nofcommands);
        if (!sub)
        {
            free(commands); // free commands before returning
            return;
        }

        /* separate commands */
        if (getokens(buff, sub, "\n") == -1)
        {
            free(commands); // free commands before returning
            free(sub); // free sub before returning
            return;
        }

         /* filling the data */
         i = 0;
         while (nofcommands)
         {
             getokens(sub[i], commands[i], " \n");
             i++, nofcommands--;
         }
         free(sub); // free sub after using it
     }

     /* the execution */
     if (commands)
     {
         execute_commands(commands, env, argv, promptNo);
         for(i=0; i<nofcommands; i++)
             free(commands[i]); // free each command after using it
         free(commands); // free commands after using them
     }

     if (av)
     {
         execute_single_command(av, env, argv, promptNo);
         check_dollar(&buff[0], state);
         for(i=0; i<ac; i++)
             free(av[i]); // free each argument after using it
         free(av); // free av after using them
     }
}



int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv,
                 char **env)
{
    char *buff = NULL;
    char ***commands = NULL;
    char **av = NULL;
    
    size_t n = 0;
    size_t promptNo = 0;
    
    int atty = -1;
    int stat = 0;
    
    ShellState state;

    state.should_exit = 0;
    state.exit_status = 0;

    while (1)
    {
        
        buff = NULL; 
	av = NULL; 
	commands = NULL; 
	promptNo++;

        if (isatty(STDIN_FILENO) == 1)
        {
            atty = 1;
            write(STDOUT_FILENO, "$ ", 2);
        }

	/* getting the input and putting it in buff */
	stat = getline(&buff, &n, stdin);

	/* If the input is "$?\n", print the exit status and continue with the next command */

	char *copy = strdup(buff); 
	if (!copy) 
	{
	    free(buff); // free buff before returning
	    return -1; 
	}
	
	if (strcmp(copy, "$?\n") == 0)
	{
	    char buffer[20];
	    int_to_str(state.exit_status, buffer); // convert state->exit_status to string
	    write(1, "Exit status: ", 13);
	    write(1, buffer, _strlen(buffer));
	    write(1, "\n", 1);
	    free(copy); // free copy after using it
	    continue;
	}
	free(copy); // free copy after using it

        check_exit(&buff[0], &state);

        if (state.should_exit)
        {
            free(buff); // free buff before exiting
            exit(state.exit_status);
        }

        replace_dollar(buff, &state);

        if (stat == -1)
        {
            if (atty == 1)
                write(STDOUT_FILENO, "\n", 1);

            break;
        }

       handle_input(buff, av, commands, env, argv, promptNo, &state);

       free(buff); // free buff after using it
   }
   return(0);
}

