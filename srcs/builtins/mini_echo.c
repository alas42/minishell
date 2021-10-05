/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:54 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:19:55 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_new_line(char **arg, int *i, int *new_line)
{
	int	j;

	while (arg[*i])
	{
		j = 0;
		if (arg[*i][j] == '-')
			j++;
		else
			return ;
		while (arg[*i][j])
		{
			if (arg[*i][j] == 'n')
				*new_line = 0;
			else
			{
				if (*i == 1)
					*new_line = 1;
				return ;
			}
			j++;
		}
		*i = *i + 1;
	}
}

int	mini_echo(t_infos *infos, t_cmd *cmd)
{
	int	i;
	int	new_line;

	(void)infos;
	new_line = 1;
	i = 1;
	is_new_line(cmd->arg, &i, &new_line);
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
		i++;
		if (cmd->arg[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
