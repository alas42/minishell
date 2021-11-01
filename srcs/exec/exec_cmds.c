/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:21:00 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 16:33:19 by avogt            ###   ########.fr       */
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
		print_error(E_CLOSE, infos);
	if (cmd->builtin)
	{
		ret = choose_builtin(infos, cmd);
		if (ret > -1)
			exit(ret);
	}
	check_errors_executable(cmd->arg[0], cmd, infos);
	if (!cmd->builtin || ret == -1)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(cmd->arg[0], cmd->arg, infos->envs);
		if (errno == EACCES)
			print_bash_error(126, cmd, infos);
	}
	exit(0);
}

static void	parent_process(t_infos *infos, t_cmd *cmd, int process_id)
{
	int	status;

	ignore_all_signals();
	if (parent_fds(infos, cmd))
		print_error(E_CLOSE, infos);
	infos->index_cmd = infos->index_cmd + 1;
	loop_through_cmds(infos);
	waitpid(process_id, &status, 0);
	if (WIFEXITED(status))
		set_error_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && status != 13)
		set_error_code(WTERMSIG(status) + 128);
	else
		set_error_code(0);
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
		parent_process(infos, cmd, process_id);
	return (1);
}
