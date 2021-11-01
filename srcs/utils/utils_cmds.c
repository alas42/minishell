/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:35 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 17:53:59 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*get_cmd(t_infos *infos)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = infos->first_cmd;
	while (i < infos->index_cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}
