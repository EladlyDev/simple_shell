#include "shell.h"

void handle_exit_status(char **av)
{
    write(1, "Exit status: ", 13);
    write(1, av[0], strlen(av[0]));
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
            exit(127);
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
    char **sub = NULL;

    /* getting the number of commands seperated by newline */
    nofcommands = noftokens(buff, "\n");

    if (nofcommands < 1)
        return;
    else if (nofcommands == 1)
    {   /* getting the number of arguments */
        int ac = noftokens(buff, " \n");
        if (ac < 1)
            return;
        /* allocating memory for the tokens */
        av = malloc(sizeof(av) * (ac + 1));
        /* filling the data */
        if (getokens(buff, av, " \n") == -1)
        {
            free(av);
            return;
        }
        /* check if command is exit status print request */
        if (av[0][0] == '0' && av[0][1] == '\0')
        {
            handle_exit_status(av);
            return;
        }
    }
    else    /* if there are more than 1 command */
    {   /* allocating memory for commands */
        commands = malloc(sizeof(*commands) * nofcommands);
        if (!commands)
            return;
        /* seperate commands */
        if (getokens(buff, sub, "\n") == -1)
        {
            free(commands);
            return;
        }

         /* filling the data */
         i = 0;
         while (nofcommands)
         {   getokens(sub[i], commands[i], " \n");
             i++, nofcommands--;
         }
     }

     /* the execution */
     if (commands)
     {
         execute_commands(commands, env, argv, promptNo);
     }

     if (av)
     {
         execute_single_command(av, env, argv, promptNo);
         check_dollar(&buff[0], state);
     }
}

int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv,
                 char **env)
{
    char *buff, ***commands, **av;
    size_t n = 0, promptNo = 0;
    int atty = -1;
    int stat = 0;
    ShellState state;

    state.should_exit = 0;
    state.exit_status = 0;

    while (1)
    {
        buff = NULL, av = NULL, commands = NULL, promptNo++;

        if (isatty(STDIN_FILENO) == 1)
        {
            atty = 1;
            write(STDOUT_FILENO, "$ ", 2);
        }

        /* getting the input and puting it in buff */
        stat = getline(&buff, &n, stdin);

        /* If the input is "$?\n", print the exit status and continue with the next command */
        if (strcmp(buff, "$?\n") == 0)
        {
            char buffer[20];
            int_to_str(state.exit_status, buffer); // convert state->exit_status to string
            write(1, "Exit status: ", 13);
            write(1, buffer, _strlen(buffer));
            write(1, "\n", 1);
            continue;
        }

        check_exit(&buff[0], &state);

        if (state.should_exit)
            exit(state.exit_status);

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

   return (0);
}

