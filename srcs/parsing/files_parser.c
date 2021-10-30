/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:03 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:29:04 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_outfile(t_token *temp, t_infos *info)
{
	if (ft_strcmp(temp->next->type, "literal"))
	{
		if (!(ft_strcmp(temp->next->type, "pipe")))
			print_pipe_error(1, info);
		print_pipe_error(2, info);
	}
	else
	{
		free(temp->next->type);
		temp->next->type = ft_strdup("outfile");
	}
}

void	get_infile(t_token *temp, t_infos *info)
{
	if (ft_strcmp(temp->next->type, "literal"))
	{
		if (!(ft_strcmp(temp->next->type, "pipe")))
			print_pipe_error(1, info);
		print_pipe_error(3, info);
	}
	else
	{
		free(temp->next->type);
		if (ft_strlen(temp->content) == 1)
			temp->next->type = ft_strdup("infile");
		else
			temp->next->type = ft_strdup("here_doc_word");
	}
}

void	parse_outfile(t_infos *info)
{
	t_token	*temp;

	temp = info->tokens;
	while (temp)
	{
		if (!(ft_strcmp(temp->type, "output_red")))
		{
			if (ft_strlen(temp->content) > 2)
				print_pipe_error(2, info);
			else if (ft_strlen(temp->content) == 2)
			{
				free(temp->type);
				temp->type = ft_strdup("double_output_red");
			}
			if (temp->next == NULL)
			{
				print_pipe_error(4, info);
				return ;
			}
			get_outfile(temp, info);
		}
		temp = temp->next;
	}
}

void	parse_infile(t_infos *info)
{
	t_token	*temp;

	temp = info->tokens;
	while (temp)
	{
		if (!(ft_strcmp(temp->type, "input_red")))
		{
			if (ft_strlen(temp->content) > 2)
				print_pipe_error(3, info);
			else if (ft_strlen(temp->content) == 2)
			{
				free(temp->type);
				temp->type = ft_strdup("here_doc");
			}
			if (temp->next == NULL)
			{
				print_pipe_error(4, info);
				return ;
			}
			get_infile(temp, info);
		}
		temp = temp->next;
	}
}
