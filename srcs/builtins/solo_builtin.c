/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:15:59 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 09:18:53 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_it_builtin(t_cmd *cmd)
{
	int		i;
	char	*builtins_str[7];

	builtins_str[B_UNSET] = "unset";
	builtins_str[B_ECHO] = "echo";
	builtins_str[B_CD] = "cd";
	builtins_str[B_ENV] = "env";
	builtins_str[B_EXIT] = "exit";
	builtins_str[B_EXPORT] = "export";
	builtins_str[B_PWD] = "pwd";
	i = -1;
	while (++i <= B_UNSET)
		if (cmd->arg[0] != NULL && !ft_strcmp(builtins_str[i], cmd->arg[0]))
			return (1);
	return (-1);
}

static int	dup_fd_builtin(t_infos *infos, t_cmd *cmd)
{
	int		ret_dup;

	ret_dup = 0;
	if (cmd->fd_infile > -1)
		ret_dup = dup2(cmd->fd_infile, STDIN_FILENO);
	if (ret_dup == -1)
		print_error(E_DUP2, infos);
	if (cmd->fd_outfile > -1)
		ret_dup = dup2(cmd->fd_outfile, STDOUT_FILENO);
	if (ret_dup == -1)
		print_error(E_DUP2, infos);
	return (1);
}

static int	close_fd_builtin(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;

	ret_close = 1;
	if (cmd->fd_infile > -1)
		ret_close = close(cmd->fd_infile);
	if (ret_close == -1)
		print_error(E_CLOSE, infos);
	if (cmd->fd_outfile > -1)
		ret_close= close(cmd->fd_outfile);
	if (ret_close == -1)
		print_error(E_CLOSE, infos);
	return (1);
}

int	solo_builtin(t_infos *infos, t_cmd *cmd)
{
	int	stdout_save;
	int	stdin_save;
	int	exit_code;

	if (is_it_builtin(cmd) == -1)
		return (-1);
	stdout_save = dup(STDOUT_FILENO);
	stdin_save = dup(STDIN_FILENO);
	dup_fd_builtin(infos, cmd);
	exit_code = choose_builtin(infos, cmd);
	infos->last_return_code = exit_code;
	close_fd_builtin(infos, cmd);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdin_save);
	close(stdout_save);
	return (1);
}
