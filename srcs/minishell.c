#include "../includes/minishell.h"

/*
**
** We shouldn't forget that envp can be NULL
**
*/
t_infos	*init_infos(char **envp)
{
	t_infos	*infos;
	char	*line_envp;

	line_envp = NULL;
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->first_env = NULL;
	infos->envs = get_env_tab(envp);
	infos->pos_path = find_pos_key(infos, "PATH");
	line_envp = get_line(infos, infos->pos_path);
	infos->paths = ft_split_char(line_envp, ':');
	infos->nb_cmd = 0;
	infos->tokens = NULL;
	infos->nb_pipe = 0;
	infos->index_cmd = 0;
	infos->first_cmd = NULL;
	infos->commands = NULL;
	g_return_code = 0;
	free(line_envp);
	return (infos);
}

/*
** Prepare the terrain
** save the stdin and out fds in case they are manipulated during the execetion part
** Launch the function that loop through all cmds nodes
*/
int	exec_cmds(t_infos *infos, char **envp)
{
	int		stdout_save;
	int		stdin_save;

	check_paths(infos);
	stdout_save = dup(STDOUT_FILENO);
	stdin_save = dup(STDIN_FILENO);
	loop_through_cmds(infos, envp);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
	return (1);
}

/*
**
** They speak about one global for exit or error status
**
*/
int	main(int ac, char **av, char **envp)
{
	int		int_mode;
	t_infos	*infos;

	(void)ac;
	(void)av;
	infos = init_infos(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	int_mode = isatty(STDIN_FILENO);
	while (int_mode)
	{
		if (int_mode == 1)
		{
			infos->line = readline("$ ");
			if (!infos->line)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				break ;
			}
			start_parsing(infos);
			if (infos->line)
				add_history(infos->line);
			check_paths(infos);
			//if (infos->nb_cmd > 1 || choose_builtin(infos, infos->first_cmd) == -1)
			//{
				//exec_cmds(infos, infos->envs);
			//}
		}
		free(infos->line);
	    free_tokens(infos);
		free_cmd_list(infos);
		int_mode = isatty(STDIN_FILENO);
	}
	//rl_clear_history();
	free_infos(infos);
	return (0);
}





//ls -l | << a cat > out1

//export AA="s -l"
//l$AA ==> ls -l

// << a << b << c cat | < c cat

