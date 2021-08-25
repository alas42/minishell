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
	// if (infos->first_cmd)
		// free_cmd_list(infos);
	free(infos);
}

void	free_tokens(t_infos *info)
{
	t_token	*temp;

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
	info->tokens = NULL;
}
