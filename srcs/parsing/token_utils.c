#include "../includes/minishell.h"


//Function to initialize the t_cmnd node
void	*cmnd_init(void)
{
	t_cmnd 	*cmd;

	cmd = (t_cmnd *)malloc(sizeof(t_cmnd));
	if (cmd == NULL)
		return (NULL);
	cmd->redirection = NULL;
	cmd->arg = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->name_infile = NULL;
	cmd->name_outfile = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

//Function to add the t_cmnd in (t_info)info->commands
void	cmd_lst_add_back(t_cmnd *cmd, t_infos *info)
{
	t_cmnd *ls;

	if (cmd == NULL)
		return;
	if (info->commands)
		ls = info->commands;
	else
	{
		info->commands = cmd;
		return;
	}
	while(ls->next)
		ls = ls->next;
	cmd->prev = ls;
	ls->next = cmd;
}

//For adding the info->commands->redirection node (t_token) in info->commands
void	red_lst_add_back(t_cmnd *cmd, t_token *new)
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

