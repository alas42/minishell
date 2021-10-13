/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:20:47 by avogt             #+#    #+#             */
/*   Updated: 2021/10/12 22:10:52 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	first_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[3];

	ret[0] = 0;
	if (infos->index_cmd != infos->nb_cmd - 1)
		ret[0] = close(infos->pipe_b[READ]);
	if (cmd->fd_infile > -1)
		ret[2] = dup2(cmd->fd_infile, STDIN_FILENO);
	else
		ret[2] = 0;
	if (cmd->fd_outfile > -1)
		ret[1] = dup2(cmd->fd_outfile, STDOUT_FILENO);
	else if (cmd->pipe_out)
		ret[1] = dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
	else
		ret[1] = 0;
	if (ret[0] > -1 && ret[1] > -1 && ret[2] > -1)
		return (0);
	return (1);
}

static int	other_cmd_odd(t_infos *infos, t_cmd *cmd)
{
	int	ret_dup[2];

	close(infos->pipe_a[READ]);
	if (cmd->fd_infile > -1)
		ret_dup[0] = dup2(cmd->fd_infile, STDIN_FILENO);
	else
		ret_dup[0] = dup2(infos->pipe_b[READ], STDIN_FILENO);
	if (cmd->fd_outfile > -1)
		ret_dup[1] = dup2(cmd->fd_outfile, STDOUT_FILENO);
	else
		ret_dup[1] = dup2(infos->pipe_a[WRITE], STDOUT_FILENO);
	close(infos->pipe_b[WRITE]);
	if (ret_dup[0] > -1 && ret_dup[1] > -1)
		return (0);
	return (1);
}

static int	other_cmd_even(t_infos *infos, t_cmd *cmd)
{
	int	ret_dup[2];

	close(infos->pipe_b[READ]);
	if (cmd->fd_infile > -1)
		ret_dup[0] = dup2(cmd->fd_infile, STDIN_FILENO);
	else
		ret_dup[0] = dup2(infos->pipe_a[READ], STDIN_FILENO);
	if (cmd->fd_outfile > -1)
		ret_dup[1] = dup2(cmd->fd_outfile, STDOUT_FILENO);
	else
		ret_dup[1] = dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
	close(infos->pipe_a[WRITE]);
	if (ret_dup[0] > -1 && ret_dup[1] > -1)
		return (0);
	return (1);
}

static int	last_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[2];

	if (infos->index_cmd % 2)
	{
		if (cmd->fd_infile > -1)
			ret[0] = dup2(cmd->fd_infile, STDIN_FILENO);
		else
			ret[0] = dup2(infos->pipe_b[READ], STDIN_FILENO);
	}
	else
	{
		if (cmd->fd_infile > -1)
			ret[0] = dup2(cmd->fd_infile, STDIN_FILENO);
		else
			ret[0] = dup2(infos->pipe_a[READ], STDIN_FILENO);
	}
	ret[1] = 0;
	if (cmd->fd_outfile > -1)
		ret[1] = dup2(cmd->fd_outfile, STDOUT_FILENO);
	if (ret[0] > -1 && ret[1] > -1)
		return (0);
	return (1);
}

int	child_fds(t_infos *infos, t_cmd *cmd)
{
	int	ret;

	if (infos->index_cmd == 0)
	{
		ret = first_cmd(infos, cmd);
	}
	else if (infos->index_cmd == infos->nb_pipe)
	{
		ret = last_cmd(infos, cmd);
	}
	else
	{
		if (infos->index_cmd % 2)
			ret = other_cmd_odd(infos, cmd);
		else
			ret = other_cmd_even(infos, cmd);
	}
	if (!ret)
		return (0);
	return (1);
}
