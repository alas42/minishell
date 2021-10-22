/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:38:06 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 15:18:55 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmds(t_infos *infos)
{
	int		stdout_save;
	int		stdin_save;

	check_paths(infos);
	stdout_save = dup(STDOUT_FILENO);
	stdin_save = dup(STDIN_FILENO);
	loop_through_cmds(infos);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdin_save);
	close(stdout_save);
	return (1);
}

void	minishell(t_infos *infos, int int_mode)
{
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
			reinit_infos(infos);
			if (infos->tokens)
			{
				infos->first_cmd = infos->commands;
				if (infos->line)
					add_history(infos->line);
				if (infos->nb_cmd > 1
					|| solo_builtin(infos, infos->first_cmd) == -1)
					exec_cmds(infos);
			}
		}
		clear_infos(infos);
		int_mode = isatty(STDIN_FILENO);
	}
}

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
	minishell(infos, int_mode);
	free_infos(infos);
	return (0);
}
