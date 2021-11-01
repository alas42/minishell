/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:42 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 15:20:49 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_error_exit(t_cmd *cmd, int code)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (code == -1)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg[1], STDERR_FILENO);
		ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
	}
	if (code == -2)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd("too many arguments", STDERR_FILENO);
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
	return ((unsigned char)(result_tmp * sign));
}

static int	is_numeric(char *str)
{
	int	i;
	int	numeric;

	numeric = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i + numeric] >= '0' && str[i + numeric] <= '9')
		numeric++;
	while (str[i + numeric] != '\0')
	{
		if (!ft_isspace(str[i + numeric]))
			return (-1);
		i++;
	}
	if (numeric > 18)
		return (-1);
	return (0);
}

int	mini_exit(t_infos *infos, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->arg[1])
	{
		exit_code = is_numeric(cmd->arg[1]);
		if (exit_code != -1)
			exit_code = ft_atoi_exit_code(cmd->arg[1]);
	}
	else
		exit_code = (unsigned char)*get_error_code();
	if (exit_code != -1)
		if (cmd->arg[1] && cmd->arg[2])
			exit_code = -2;
	if (exit_code < 0)
		ft_error_exit(cmd, exit_code);
	if (exit_code == -2)
		return (1);
	free_infos(infos);
	if (exit_code == -1)
		exit(2);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_code);
}
