/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:21:06 by avogt             #+#    #+#             */
/*   Updated: 2021/10/12 22:11:50 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	first_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret_close[3];

	ret_close[0] = 0;
	if (infos->index_cmd != infos->nb_cmd - 1)
		ret_close[0] = close(infos->pipe_b[WRITE]);
	if (cmd->fd_infile > -1)
		ret_close[1] = close(cmd->fd_infile);
	else
		ret_close[1] = 0;
	if (cmd->fd_outfile > -1)
		ret_close[2] = close(cmd->fd_outfile);
	else
		ret_close[2] = 0;
	if (ret_close[0] > -1 && ret_close[1] > -1 && ret_close[2] > -1)
		return (0);
	return (1);
}

static int	other_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[4];

	if (infos->index_cmd % 2)
	{
		ret[0] = close(infos->pipe_b[READ]);
		ret[1] = close(infos->pipe_a[WRITE]);
	}
	else
	{
		ret[0] = close(infos->pipe_a[READ]);
		ret[1] = close(infos->pipe_b[WRITE]);
	}
	ret[2] = 0;
	ret[3] = 0;
	if (cmd->fd_infile > -1)
		ret[2] = close(cmd->fd_infile);
	if (cmd->fd_outfile > -1)
		ret[3] = close(cmd->fd_outfile);
	if (ret[0] > -1 && ret[1] > -1 && ret[2] > -1 && ret[3] > -1)
		return (0);
	return (1);
}

static int	last_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[3];

	if (infos->index_cmd % 2)
	{
		ret[0] = close(infos->pipe_b[READ]);
	}
	else
	{
		ret[0] = close(infos->pipe_a[READ]);
	}
	ret[1] = 0;
	ret[2] = 0;
	if (cmd->fd_infile > -1)
		ret[1] = close(cmd->fd_infile);
	if (cmd->fd_outfile > -1)
		ret[2] = close(cmd->fd_outfile);
	if (ret[0] > -1 && ret[1] > -1 && ret[2] > -1)
		return (0);
	return (1);
}

int	parent_fds(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;

	if (infos->index_cmd == 0)
		ret_close = first_cmd(infos, cmd);
	else if (infos->index_cmd == infos->nb_pipe)
		ret_close = last_cmd(infos, cmd);
	else
		ret_close = other_cmd(infos, cmd);
	if (!ret_close)
		return (0);
	return (1);
}
