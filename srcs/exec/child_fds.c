#include "../../includes/minishell.h"

static int	first_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;
	int	ret_dup;

	ret_dup = 0;
	ret_close = 0;
	ret_close = close(infos->pipe_b[READ]);
	if (cmd->name_infile != NULL)
	{
		cmd->fd_infile = open(cmd->name_infile, O_RDONLY, 0644);
		ret_dup = dup2(cmd->fd_infile, STDIN_FILENO);
	}
	if (cmd->pipe_out)
		ret_dup = dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
	else if (cmd->name_outfile != NULL)
	{
		cmd->fd_outfile = open(cmd->name_outfile,
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
		ret_dup = dup2(cmd->fd_outfile, STDOUT_FILENO);
	}
	if (ret_close > -1 && ret_dup > -1)
		return (0);
	return (1);
}

static int	other_cmd(t_infos *infos)
{
	int	ret_dup;

	ret_dup = 0;
	if (infos->index_cmd % 2)
	{
		ret_dup = dup2(infos->pipe_b[READ], STDIN_FILENO);
		ret_dup = dup2(infos->pipe_a[WRITE], STDOUT_FILENO);
	}
	else
	{
		ret_dup = dup2(infos->pipe_a[READ], STDIN_FILENO);
		ret_dup = dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
	}
	if (ret_dup > -1)
		return (0);
	return (1);
}

static int	last_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;
	int	ret_dup;

	ret_dup = 0;
	ret_close = 0;
	if (infos->index_cmd % 2)
	{
		ret_dup = dup2(infos->pipe_b[READ], STDIN_FILENO);
		ret_close = close(infos->pipe_b[WRITE]);
	}
	else
	{
		ret_dup = dup2(infos->pipe_a[READ], STDIN_FILENO);
		ret_close = close(infos->pipe_a[WRITE]);
	}
	if (cmd->name_outfile != NULL)
	{
		cmd->fd_outfile = open(cmd->name_outfile,
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
		ret_dup = dup2(cmd->fd_outfile, STDOUT_FILENO);
	}
	if (ret_dup > -1 && ret_close > -1)
		return (0);
	return (1);
}

int	child_fds(t_infos *infos, t_cmd *cmd)
{
	int	ret;

	ret = 0;
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
