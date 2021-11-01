/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:28:57 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 03:50:43 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dollar_type(t_infos *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "literal_space")))
		{
			if (ft_strlen(token->content) == 0)
			{
				free(token->type);
				token->type = ft_strdup("space");
			}
			else
			{
				free(token->type);
				token->type = ft_strdup("literal");
			}
		}
		token = token->next;
	}
}

void	check_only_dollar(t_infos *info)
{
	t_token  *token;

	token = info->tokens;
	while(token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
		{
			if (ft_strlen(token->content) <= 1)
			{
				free(token->type);
				token->type = ft_strdup("literal");
			}
			else if (!(ft_isalpha(token->content[1])) 
			&& !(ft_isdigit(token->content[1]))
			&& token->content[1] != '?')
			{
				free(token->type);
				token->type = ft_strdup("literal");
			}
		}
		token = token->next;
	}
}

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
