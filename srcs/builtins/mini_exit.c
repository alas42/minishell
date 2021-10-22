/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:42 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 15:09:01 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_error_exit(t_cmd *cmd, int code)
{
	if (code == -1)
	{
		ft_putstr_fd("minishell: exit: " ,STDERR_FILENO);
		ft_putstr_fd(cmd->arg[1],STDERR_FILENO);
		ft_putendl_fd(" : argument numérique nécéssaire", STDERR_FILENO);
	}
	if (code == -2)
	{
		ft_putstr_fd("minishell: exit: " ,STDERR_FILENO);
		ft_putendl_fd("trop d'arguments", STDERR_FILENO);
	}
}

static int	ft_atoi_exit_code(const char *str)
{
	int	sign;
	int	result_tmp;

	result_tmp = 0;
	sign = 1;
	while (ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
		result_tmp = (result_tmp * 10) + (*str++ - '0');
	if (*str != '\0' && !ft_isspace(*str))
		return (-1);
	return ((unsigned char)result_tmp * sign);
}

int	mini_exit(t_infos *infos, t_cmd *cmd)
{
	int	exit_code;

	(void)cmd;
	exit_code = 0;
	if (cmd->arg[1])
		exit_code = ft_atoi_exit_code(cmd->arg[1]);
	else
		exit_code = (unsigned char)infos->last_return_code;
	if (exit_code != -1)
	{
		if (cmd->arg[1] && cmd->arg[2])
				exit_code = -2;
	}
	if (exit_code < 0)
		ft_error_exit(cmd, exit_code);
	if (exit_code == -2)
		return (1);
	free_infos(infos);
	rl_clear_history();
	if (exit_code == -1)
		exit(1);
	exit(exit_code);
}
