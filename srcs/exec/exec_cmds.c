/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:21:00 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:22:31 by avogt            ###   ########.fr       */
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

static void	child_process(t_infos *infos, t_cmd *cmd, char **envp)
{
	int	ret;

	ret = 0;
	if (child_fds(infos, cmd))
	{
		ft_putendl_fd("close or dup2 error in child", STDERR_FILENO);
	}
	if (cmd->builtin)
	{
		ret = choose_builtin(infos, cmd);
	}
	if (!cmd->builtin || ret == -1)
	{
		execve(cmd->arg[0], cmd->arg, envp);
		print_error(E_EXECVE, infos);
	}
	else
	{
		ft_putendl_fd("Something went wrong", STDERR_FILENO);
	}
}

static void	parent_process(t_infos *infos, t_cmd *cmd, char **envp)
{
	int	status;

	if (parent_fds(infos, cmd))
	{
		ft_putendl_fd("close error in parent", STDERR_FILENO);
	}
	infos->index_cmd = infos->index_cmd + 1;
	loop_through_cmds(infos, envp);
	wait(&status);
/*
**
** if (WIFEXITED(status))
**    printf("Exit status: %d\n", WEXITSTATUS(status));
** else if (WIFSIGNALED(status))
**    psignal(WTERMSIG(status), "Exit signal");
** set the ? (NOT AN ENV VAR) to its correct return code (127 + ...)
*/
}

int	loop_through_cmds(t_infos *infos, char **envp)
{
	t_cmd	*cmd;
	int		process_id;

	cmd = get_cmd(infos);
	if (!cmd)
		return (1);
	piping(infos);
	process_id = fork();
	if (process_id == 0)
		child_process(infos, cmd, envp);
	else if (process_id == -1)
		print_error(E_FORK, infos);
	else
		parent_process(infos, cmd, envp);
	return (1);
}
