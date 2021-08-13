#include "../includes/minishell.h"

/*
**
** We shouldn't forget that envp can be NULL
**
*/

t_infos	*init_infos(char **envp)
{
	t_infos	*infos;

	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->first_env = NULL;
	infos->envs = get_env_tab(envp);
	get_env_list(infos, infos->envs);
	infos->pos_path = find_pos_key(infos, "PATH");
	infos->paths = ft_split_char(get_pair(infos, infos->pos_path), ':');
	infos->nb_cmd = 0;
	infos->tokens = NULL;
	infos->nb_pipe = 0;
	infos->index_cmd = 0;
	infos->first_cmd = NULL;
	return (infos);
}

/*
**
** They speak about one global for exit or error status
** don't know what structure we will be using but there's a start I guess
**
** Step 1: DONE
** An elaborate pipex that can execute only one func if there is no pipe
** but more than two if needed
**
** Step 1.1:
** Parsing without execptions to fill structs with correct infos
**
** Step 1.2: DONE
** Recursive or looping method that executes cmds with correct pipes
**
** Step 1.3:
** Add exceptions to parsing - check for builtins
**
** Step 1.4:
** Check if it is an interaction with the terminal
** or a normal line
**
*/

int	main(int ac __attribute__((unused)),
	char **av __attribute__((unused)), char **envp)
{
	int		int_mode;
	t_infos	*infos;

	infos = init_infos(envp);
	signal(SIGINT, sigint_handler); //CTRL + C
	signal(SIGQUIT, sigquit_handler); // CTRL + BACKSLASH
	int_mode = isatty(STDIN_FILENO);
	while (int_mode)
	{
		if (int_mode == 1)
		{
			infos->line = readline("$ ");
			if (!infos->line)
			{ //CTRL + D
				ft_putendl_fd("exit", STDOUT_FILENO);
				break ;
			}
			start_parsing(infos);
			if (infos->line)
				add_history(infos->line);
			/*if (infos->nb_cmd > 1 || choose_builtin(infos, infos->first_cmd) == -1)
			{
				//it's either multiples commands OR only one that is not a builtin
				exec_cmds(infos, infos->envs);
			}*/
		}
		free(infos->line);
		int_mode = isatty(STDIN_FILENO);
	}
	rl_clear_history();
	free_infos(infos);
	free(infos);
	return (0);
}
