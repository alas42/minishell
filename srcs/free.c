#include "../includes/minishell.h"

void	ft_free_tab_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_infos(t_infos *infos)
{
	t_cmd *cmd;
	t_cmd *next;

	cmd = infos->first;
	free(infos->line);
	while (cmd)
	{
		ft_free_tab_ptr(cmd->arg);
		cmd = cmd->next;
	}
	cmd = infos->first;
	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

void	free_tokens(t_infos *info)
{
	t_token *temp;

	if (info->tokens == NULL)
		return ;
	while (info->tokens->next != NULL)
	{
		temp = ft_lstlast(info->tokens);
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
}