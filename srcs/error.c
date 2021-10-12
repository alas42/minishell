/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:27:46 by avogt             #+#    #+#             */
/*   Updated: 2021/10/12 17:26:21 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int state, t_infos *infos)
{
	ft_putstr_fd("minishell: System function failed: ", STDERR_FILENO);
	if (state == E_MALLOC)
		ft_putendl_fd("Allocation error", STDERR_FILENO);
	else if (state == E_OPEN)
		ft_putendl_fd("Open error", STDERR_FILENO);
	else if (state == E_CLOSE)
		ft_putendl_fd("Close error", STDERR_FILENO);
	else if (state == E_FORK)
		ft_putendl_fd("Fork error", STDERR_FILENO);
	else if (state == E_PIPE)
		ft_putendl_fd("Pipe error", STDERR_FILENO);
	else if (state == E_DUP)
		ft_putendl_fd("Dup error", STDERR_FILENO);
	else if (state == E_DUP2)
		ft_putendl_fd("Dup2 error", STDERR_FILENO);
	else if (state == E_EXECVE)
		ft_putendl_fd("Execve error", STDERR_FILENO);
	infos->last_return_code = 1;
	free_infos(infos);
	exit(infos->last_return_code);
}

void	print_bash_error(int state, t_cmd *cmd)
{
	char	*m;
	char	*cmd_name;
	char	*message;
	char	*tmp;
	int		len;

	m = "minishell: \0";
	cmd_name = ft_strdup(cmd->arg[0]);
	if (state == 127)
		message = " : command not found\0";
	else if (state == 126)
		message = " : command cannot be invoked\0";
	else
		message = " : error\0";
	len = ft_strlen(m) + ft_strlen(cmd_name) + ft_strlen(message);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	tmp[0] = '\0';
	tmp = ft_strcat(tmp, m);
	tmp = ft_strcat(tmp, cmd_name);
	tmp = ft_strcat(tmp, message);
	ft_putendl_fd(tmp, STDERR_FILENO);
	free(cmd_name);
	free(tmp);
	exit(state);
}
