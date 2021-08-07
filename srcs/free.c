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
	free(infos->line);
	ft_free_tab_ptr(infos->paths);
	ft_free_tab_ptr(infos->envs);
	free_env_list(infos);
	free_cmd_list(infos);
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