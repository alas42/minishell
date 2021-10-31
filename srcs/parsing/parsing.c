/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:28:28 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 13:56:30 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_last_space_tokens(t_token *temp)
{
	if (temp && !(ft_strncmp(temp->type, "space", 5)))
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
		free(temp->content);
		free(temp->type);
		free(temp);
	}
}

void	remove_space_tokens(t_infos *info)
{
	t_token	*temp;
	int		i;

	temp = info->tokens;
	i = 0;
	if (temp != NULL && temp->next == NULL)
	{
		if (!(ft_strncmp(temp->type, "space", 5)))
		{
			free(temp->content);
			free(temp->type);
			free(temp);
			info->tokens = NULL;
		}
		return ;
	}
	while (temp && temp->next)
	{
		if (!(ft_strncmp(temp->type, "space", 5)))
		{
			merge_tokens(info, i, 1);
			temp = info->tokens;
			i = 0;
		}
		temp = temp->next;
		i++;
	}
	remove_last_space_tokens(temp);
}

void	check_pipe_error(t_infos *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "literal")))
		{
			if (ft_strlen(token->content) == 0)
			{
				free(token->type);
				token->type = ft_strdup("space");
			}
		}
		if (!(ft_strcmp(token->type, "pipe")))
		{
			if (ft_strlen(token->content) > 1 || token->pos == 0
				|| token->next == NULL)
				print_pipe_error(1, info);
			if (token->next && !(ft_strcmp(token->next->type, "pipe")))
				print_pipe_error(1, info);
		}
		token = token->next;
	}		
}

void	start_parsing(t_infos *info)
{
	add_to_struct(info);
	if (info->tokens == NULL)
		return ;
	get_dollar(info);
	check_quotes(info);	
	expand_dollar(info);
	merge_same(info);
	remove_space_tokens(info);
	if (info->tokens == NULL)
		return;
	parse_outfile(info);
	parse_infile(info);
	check_pipe_error(info);
	remove_space_tokens(info);
	if (info->tokens == NULL)
		return;
	move_to_cmd(info);
	handle_redirections(info);
}
