/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:28:05 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 15:29:39 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (infos->envs)
		ft_free_tab_ptr(infos->envs);
	if (infos->first_cmd)
		free_cmnds(infos);
	if (infos->tokens)
		free_tokens(infos);
	free(infos);
	clear_history();
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

void	free_red_tokens(t_cmd *com)
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
