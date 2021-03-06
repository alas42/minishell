/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:31 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:29:32 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_token_type(t_token *new, t_infos *info, int i)
{
	if (info->line[i] == '|')
		new->type = ft_strdup("pipe");
	else if (info->line[i] == '<')
		new->type = ft_strdup("input_red");
	else if (info->line[i] == '>')
		new->type = ft_strdup("output_red");
	else if (info->line[i] == 39)
		new->type = ft_strdup("single_quote");
	else if (info->line[i] == 34)
		new->type = ft_strdup("double_quote");
	else if (info->line[i] == '$')
		new->type = ft_strdup("dollar");
	else if (ft_isspace_isdigit(info->line[i], 's'))
		new->type = ft_strdup("space");
	else
		new->type = ft_strdup("literal");
}

t_token	*token_init(void)
{
	t_token	*data;

	data = (t_token *)malloc(sizeof(t_token));
	if (data == NULL)
		return (NULL);
	data->content = NULL;
	data->type = NULL;
	data->pos = -1;
	data->next = NULL;
	data->prev = NULL;
	return (data);
}

void	lst_add_back(t_infos *info, t_token *new)
{
	t_token	*ls;

	if (new == NULL)
		return ;
	if (info->tokens)
		ls = info->tokens;
	else
	{
		info->tokens = new;
		return ;
	}
	while (ls->next != NULL)
		ls = ls->next;
	new->prev = ls;
	ls->next = new;
}

t_token	*ft_lstlast_token(t_token *lst)
{
	t_token	*p;

	p = lst;
	if (lst == NULL)
		return (NULL);
	while (p->next != NULL)
		p = p->next;
	return (p);
}

void	add_to_struct(t_infos *info)
{
	int		i;
	t_token	*new;

	i = 0;
	while (info->line[i] != '\0')
	{
		new = token_init();
		if (new == NULL)
			print_error(E_MALLOC, info);
		new->content = char_to_str(info->line[i], info);
		new->pos = i;
		get_token_type(new, info, i);
		lst_add_back(info, new);
		i++;
	}
}
