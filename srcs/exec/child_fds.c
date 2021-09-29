#include "../../includes/minishell.h"

static int	first_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[3];

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

static int	other_cmd(t_infos *infos)
{
	int	ret_dup[2];

	if (infos->index_cmd % 2)
	{
		ret_dup[0] = dup2(infos->pipe_b[READ], STDIN_FILENO);
		ret_dup[1] = dup2(infos->pipe_a[WRITE], STDOUT_FILENO);
	}
	else
	{
		ret_dup[0] = dup2(infos->pipe_a[READ], STDIN_FILENO);
		ret_dup[1] = dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
	}
	if (ret_dup[0] > -1 && ret_dup[1] > -1)
		return (0);
	return (1);
}

static int	last_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret[3];

	if (infos->index_cmd % 2)
	{
		if (cmd->fd_infile > -1)
			ret[0] = dup2(cmd->fd_infile, STDIN_FILENO);
		else
			ret[0] = dup2(infos->pipe_b[READ], STDIN_FILENO);
		ret[1] = close(infos->pipe_b[WRITE]);
	}
	else
	{
		if (cmd->fd_infile > -1)
			ret[0] = dup2(cmd->fd_infile, STDIN_FILENO);
		else
			ret[0] = dup2(infos->pipe_a[READ], STDIN_FILENO);
		ret[1] = close(infos->pipe_a[WRITE]);
	}
	if (cmd->fd_outfile > -1)
		ret[2] = dup2(cmd->fd_outfile, STDOUT_FILENO);
	else
		ret[2] = 0;
	if (ret[0] > -1 && ret[1] > -1 && ret[2] > -1)
		return (0);
	return (1);
}

int	child_fds(t_infos *infos, t_cmd *cmd)
{
	int	ret;

	if (infos->index_cmd == 0)
		ret = first_cmd(infos, cmd);
	else if (infos->index_cmd == infos->nb_pipe)
		ret = last_cmd(infos, cmd);
	else
		ret = other_cmd(infos);
	if (!ret)
		return (0);
	return (1);
}
