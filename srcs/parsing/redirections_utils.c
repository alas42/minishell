/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:57 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:29:58 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_last_input_red(t_cmd *cmd, int pos)
{
	t_token	*red;
	int		i;

	i = 0;
	red = cmd->redirection;
	while (i++ < pos)
		red = red->next;
	while (red)
	{
		if (!(ft_strcmp(red->type, "here_doc"))
			|| !(ft_strcmp(red->type, "input_red")))
			return (red->pos);
		red = red->next;
	}
	return (0);
}

int	fd_write(int fd, char *line)
{
	int	i;
	int	nl;

	nl = 10;
	i = 0;
	while (line[i])
	{
		write(fd, &line[i], 1);
		i++;
	}
	write(fd, &nl, 1);
	return (i);
}
