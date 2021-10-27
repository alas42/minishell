/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:21:00 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 16:30:54 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	choose_builtin(t_infos *infos, t_cmd *cmd)
{
	int		i;
	char	*builtins_str[7];
	int		(*builtins[7])(t_infos *infos, t_cmd *cmd);

	builtins[B_UNSET] = mini_unset;
	builtins[B_ECHO] = mini_echo;
	builtins[B_PWD] = mini_pwd;
	builtins[B_EXPORT] = mini_export;
	builtins[B_CD] = mini_cd;
	builtins[B_EXIT] = mini_exit;
	builtins[B_ENV] = mini_env;
	builtins_str[B_UNSET] = "unset";
	builtins_str[B_ECHO] = "echo";
	builtins_str[B_CD] = "cd";
	builtins_str[B_ENV] = "env";
	builtins_str[B_EXIT] = "exit";
	builtins_str[B_EXPORT] = "export";
	builtins_str[B_PWD] = "pwd";
	i = -1;
	while (++i <= B_UNSET)
		if (!ft_strcmp(builtins_str[i], cmd->arg[0]))
			return ((*builtins[i])(infos, cmd));
	return (-1);
}

static void	piping(t_infos *infos)
{
	if (infos->index_cmd != infos->nb_cmd - 1)
	{
		if (infos->index_cmd % 2)
		{
			if (pipe(infos->pipe_a) == -1)
				print_error(E_PIPE, infos);
		}
		else
		{
			if (pipe(infos->pipe_b) == -1)
				print_error(E_PIPE, infos);
		}
	}
}

static void	child_process(t_infos *infos, t_cmd *cmd)
{
	int	ret;

	ret = -1;
	if (child_fds(infos, cmd))
	{
		print_error(E_CLOSE, infos);
	}
	if (cmd->builtin)
	{
		ret = choose_builtin(infos, cmd);
		if (ret > -1)
			return ;
	}
	if (!cmd->builtin || ret == -1)
	{
		execve(cmd->arg[0], cmd->arg, infos->envs);
	}
	if (!ft_exists(cmd->arg[0]))
		print_bash_error(127, cmd);
	else
		print_bash_error(126, cmd);
}

static void	parent_process(t_infos *infos, t_cmd *cmd)
{
	int	status;

	if (parent_fds(infos, cmd))
	{
		print_error(E_CLOSE, infos);
	}
	infos->index_cmd = infos->index_cmd + 1;
	loop_through_cmds(infos);
	wait(&status);
	if (WIFEXITED(status))
		infos->last_return_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		infos->last_return_code = WTERMSIG(status) + 128;
	else
		infos->last_return_code = 1;
}

int	loop_through_cmds(t_infos *infos)
{
	t_cmd	*cmd;
	int		process_id;

	cmd = get_cmd(infos);
	if (!cmd)
		return (1);
	piping(infos);
	process_id = fork();
	if (process_id == 0)
		child_process(infos, cmd);
	else if (process_id == -1)
		print_error(E_FORK, infos);
	else
		parent_process(infos, cmd);
	return (1);
}
