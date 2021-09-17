#include "../includes/minishell.h"

void	ft_free_tab_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}

void	free_infos(t_infos *infos)
{
	if (infos->line)
		free(infos->line);
	if (infos->paths)
		ft_free_tab_ptr(infos->paths);
	if (infos->envs)
		ft_free_tab_ptr(infos->envs);
	if (infos->first_cmd)
		free_cmd_list(infos);
	if (infos->tokens)
		free_tokens(infos);
	free(infos);
}

void	free_tokens(t_infos *info)
{
	t_token	*temp;

	if (info->tokens == NULL)
		return ;
	while (info->tokens->next != NULL)
	{
		temp = ft_lstlast_token(info->tokens);
		free(temp->type);
		free(temp->content);
		temp->prev->next = NULL;
		free(temp);
	}
	if (info->tokens != NULL)
	{
		free(info->tokens->content);
		free(info->tokens->type);
		free(info->tokens);
	}
	info->tokens = NULL;
}


void	free_red_tokens(t_cmnd *com)
{
	t_token	*temp;

	if (com->redirection == NULL)
		return ;
	while (com->redirection->next != NULL)
	{
		temp = ft_lstlast_token(com->redirection);
		free(temp->type);
		free(temp->content);
		temp->prev->next = NULL;
		free(temp);
	}
	if (com->redirection != NULL)
	{
		free(com->redirection->content);
		free(com->redirection->type);
		free(com->redirection);
	}
	com->redirection = NULL;
}

void    free_cmnds(t_infos *info)
{
	t_cmnd  *com;
	t_cmnd  *temp_com;

	if (info->commands == NULL)
		return ;
	com = info->commands;
	while (com->next != NULL)
	{
		temp_com = ft_lstlast_cmd(info->commands);
		if (temp_com->arg)
			free_doub_char(temp_com->arg);
	 	free_red_tokens(temp_com);
		temp_com->prev->next = NULL;
		free(temp_com);
	}
	if (com)
	{
		if (com->arg)
			free_doub_char(com->arg);
		free_red_tokens(com);
		free(com);
		info->commands = NULL;
	}
}
