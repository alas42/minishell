#include "../../includes/minishell.h"

/*
**
** Creating nodes and adding them to the list
**
*/

void	add_cmd(t_infos *infos, t_cmd *new)
{
	t_cmd *tmp;

	tmp = infos->first_cmd;
	new->next = NULL;
	if (tmp == NULL)
	{
		new->prec = NULL;
		infos->first_cmd = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		new->prec = tmp;
		tmp->next = new;
	}
	if (new->pipe_in)
		infos->nb_pipe = infos->nb_pipe + 1;
	infos->nb_cmd = infos->nb_cmd + 1;
}

t_cmd	*creating_cmd(char **arg, int pipe_in, int pipe_out)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = arg;
	cmd->pipe_in = pipe_in;
	cmd->pipe_out = pipe_out;
	cmd->name_infile = NULL;
	cmd->name_outfile = NULL;
	cmd->builtin = 0;
	cmd->process = 1;
	return (cmd);
}

/*
**
** Returns the t_cmd node thank to the index infos->index_cmd
**
** Maybe I will change it to a integer as second param
**
*/

t_cmd	*get_cmd(t_infos *infos)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = infos->first_cmd;
	while (i < infos->index_cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

void	free_cmd_list(t_infos *infos)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = infos->first_cmd;
	while (cmd)
	{
		tmp = cmd;
		if (cmd->name_infile)
			free(cmd->name_infile);
		if (cmd->name_outfile)
			free(cmd->name_outfile);
		ft_free_tab_ptr(cmd->arg);
		cmd = cmd->next;
		free(tmp);
	}
}
