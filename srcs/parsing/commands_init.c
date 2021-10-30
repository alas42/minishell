#include "../includes/minishell.h"

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*p;

	p = lst;
	if (lst == NULL)
		return (NULL);
	while (p->next != NULL)
		p = p->next;
	return (p);
}

void	*cmnd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->redirection = NULL;
	cmd->arg = NULL;
	cmd->builtin = -1;
	cmd->index = -1;
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->process = -1;
	cmd->fd_infile = -1;
	cmd->fd_outfile = -1;
	cmd->here_doc = 0;
	cmd->name_infile = NULL;
	cmd->name_outfile = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	cmd_lst_add_back(t_cmd *cmd, t_infos *info)
{
	t_cmd	*ls;

	if (cmd == NULL)
		return ;
	if (info->commands)
		ls = info->commands;
	else
	{
		info->commands = cmd;
		return ;
	}
	while (ls->next)
		ls = ls->next;
	cmd->prev = ls;
	ls->next = cmd;
}

void	red_lst_add_back(t_cmd *cmd, t_token *new)
{
	t_token	*ls;

	if (new == NULL)
		return ;
	if (cmd->redirection)
		ls = cmd->redirection;
	else
	{
		cmd->redirection = new;
		return ;
	}
	while (ls->next != NULL)
		ls = ls->next;
	new->prev = ls;
	ls->next = new;
}
