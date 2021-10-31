/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:28:57 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:28:57 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_dollar_prev(t_infos *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
		{
			if (token->prev != NULL
				&& !(ft_strcmp(token->prev->type, "literal")))
				merge_tokens(info, token->prev->pos, 1);
		}
		token = token->next;
	}
}

void	update_dollar_type(t_infos *info, int pos)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = info->tokens;
	while (i < pos)
	{
		temp = temp->next;
		i++;
	}
	free(temp->type);
	temp->type = ft_strdup("dollar");
}

void	get_dollar(t_infos *info)
{
	t_token	*temp;
	int		i;
	int		counter;

	i = 0;
	temp = info->tokens;
	while (temp && (ft_strcmp(temp->type, "pipe")))
	{
		counter = 0;
		if (ft_strcmp(temp->type, "dollar") == 0 && temp->next != NULL
			&& !(ft_strcmp(temp->next->type, "literal")))
		{
			merge_tokens(info, i, 1);
			update_dollar_type(info, i);
			temp = info->tokens;
			counter = 1;
			i = 0;
		}
		if (counter != 1)
		{
			i++;
			temp = temp->next;
		}
	}
}
