#include "../../includes/minishell.h"

static int	first_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;

	ret_close = 0;
	ret_close = close(infos->pipe_b[WRITE]);
	if (cmd->name_infile != NULL)
		ret_close = close(cmd->fd_infile);
	if (cmd->name_outfile != NULL)
		ret_close = close(cmd->fd_outfile);
	return (ret_close);
}

static int	other_cmd(t_infos *infos)
{
	int	ret_close;

	ret_close = 0;
	if (infos->index_cmd % 2)
	{
		ret_close = close(infos->pipe_b[READ]);
		ret_close = close(infos->pipe_a[WRITE]);
	}
	else
	{
		ret_close = close(infos->pipe_a[READ]);
		ret_close = close(infos->pipe_b[WRITE]);
	}
	return (ret_close);
}

static int	last_cmd(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;

	ret_close = 0;
	if (infos->index_cmd % 2)
	{
		ret_close = close(infos->pipe_b[READ]);
		ret_close = close(infos->pipe_b[WRITE]);
	}
	else
	{
		ret_close = close(infos->pipe_a[READ]);
		ret_close = close(infos->pipe_a[WRITE]);
	}
	if (cmd->name_outfile != NULL)
		ret_close = close(cmd->fd_outfile);
	return (ret_close);
}

int	parent_fds(t_infos *infos, t_cmd *cmd)
{
	int	ret_close;

	ret_close = 0;
	if (infos->index_cmd == 0)
		ret_close = first_cmd(infos, cmd);
	else if (infos->index_cmd == infos->nb_pipe)
		ret_close = last_cmd(infos, cmd);
	else
		ret_close = other_cmd(infos);
	if (ret_close > -1)
		return (0);
	return (1);
}
