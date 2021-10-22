/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:22:45 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 15:25:02 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmnds_2(t_infos *info, t_cmd *com)
{
	if (com)
	{
		if (com->arg)
			free_doub_char(com->arg);
		free_red_tokens(com);
		if (com->name_infile)
			free(com->name_infile);
		if (com->name_outfile)
			free(com->name_outfile);
		free(com);
		info->commands = NULL;
	}
}

void	free_cmnds(t_infos *info)
{
	t_cmd	*com;
	t_cmd	*temp_com;

	if (info->commands == NULL)
		return ;
	com = info->commands;
	while (com->next != NULL)
	{
		temp_com = ft_lstlast_cmd(info->commands);
		if (temp_com->arg)
			free_doub_char(temp_com->arg);
		free_red_tokens(temp_com);
		if (temp_com->name_infile)
			free(temp_com->name_infile);
		if (temp_com->name_outfile)
			free(temp_com->name_outfile);
		temp_com->prev->next = NULL;
		free(temp_com);
	}
	free_cmnds_2(info, com);
}
