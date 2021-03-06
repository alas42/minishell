/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:38:06 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 16:49:14 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmds(t_infos *infos)
{
	int		stdout_save;
	int		stdin_save;

	if (infos->first_cmd->arg && infos->first_cmd->arg[0] != NULL)
	{
		check_paths(infos);
		stdout_save = dup(STDOUT_FILENO);
		stdin_save = dup(STDIN_FILENO);
		loop_through_cmds(infos);
		dup2(stdin_save, STDIN_FILENO);
		dup2(stdout_save, STDOUT_FILENO);
		close(stdin_save);
		close(stdout_save);
	}
	return (1);
}

void	minishell(t_infos *infos, int int_mode)
{
	while (int_mode)
	{
		set_signals();
		if (int_mode == 1)
		{
			infos->line = readline("$ ");
			if (!infos->line)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				break ;
			}
			if (infos->line && ft_strlen(infos->line) >= 1)
				add_history(infos->line);
			reinit_infos(infos);
			if (infos->tokens && infos->parse_error == 0)
			{
				infos->first_cmd = infos->commands;
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

	infos = init_infos(envp);
	int_mode = isatty(STDIN_FILENO);
	minishell(infos, int_mode);
	free_infos(infos);
	return (0);
	(void)ac;
	(void)av;
}
