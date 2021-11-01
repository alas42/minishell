/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:18 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 04:40:53 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_tokens_pos(t_infos *info)
{
	int		i;
	t_token	*temp;

	temp = info->tokens;
	i = 0;
	while (temp)
	{
		temp->pos = i;
		i++;
		temp = temp->next;
	}
}

t_token	*join_tokens(t_token *tokens)
{
	t_token	*second;
	char	*temp;
	int		i;

	i = 1;
	second = tokens->next;
	temp = second->content;
	i = ft_isallspace(tokens->content);
	if (i == 0)
		second->content = ft_strdup(temp);
	else
		second->content = ft_strjoin(tokens->content, temp);
	tokens->next = NULL;
	second->prev = NULL;
	free(temp);
	free(tokens->content);
	free(tokens->type);
	free(tokens);
	tokens = second;
	return (tokens);
}

void	merge_tokens(t_infos *info, int start, int total)
{
	t_token	*one;
	int		i;

	i = 0;
	if (total < 1)
		return ;
	if (start == 0)
	{
		while (i++ < total)
			info->tokens = join_tokens(info->tokens);
		update_tokens_pos(info);
		return ;
	}
	one = info->tokens;
	while (i++ < start)
		one = one->next;
	one->prev->next = NULL;
	one->prev = NULL;
	i = 0;
	while (i++ < total)
		one = join_tokens(one);
	lst_add_back(info, one);
	update_tokens_pos(info);
	return ;
}

void	merge_same(t_infos *info)
{
	t_token	*temp;
	char	*tmp_type;
	int		j;
	int		i;

	j = 0;
	i = 0;
	temp = info->tokens;
	tmp_type = temp->type;
	while (temp)
	{
		if (!(ft_strcmp(tmp_type, temp->type)))
		{
			j++;
			temp = temp->next;
		}
		else
		{
			tmp_type = temp->type;
			merge_tokens(info, i, j - 1);
			i++;
			j = 0;
		}
	}
	merge_tokens(info, i, j - 1);
}
