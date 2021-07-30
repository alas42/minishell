/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:14:32 by avogt             #+#    #+#             */
/*   Updated: 2021/07/05 14:55:17 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	not_found(char *path, int nb_process, int nb, t_helper *helper)
{
	if (nb == 0)
		ft_putstr_fd("command not found: ", 2);
	if (nb == 1)
	{
		ft_putstr_fd("No such file or directory: ", 2);
		if (nb_process == 0)
			helper->fd_infile = 0;
	}
	ft_putstr_fd(path, 2);
	ft_write_fd('\n', 2);
	helper->process[nb_process] = -1;
}

void	ft_usage(void)
{
	ft_putstr_fd("Usage:\ninfile cmd1 cmd2 outfile\n", 2);
	exit(1);
}

void	ft_error_functions(int nb, t_helper *helper)
{
	ft_putstr_fd("Error\n", 2);
	if (nb == 0)
		ft_putstr_fd("parsing of commands returns an error\n", 2);
	else if (nb == 1)
		ft_putstr_fd("parsing of env variable PATH returns an error\n", 2);
	ft_free_struct_helper(helper);
	ft_usage();
	exit(1);
}

void	ft_error_sysfunctions(int nb, t_helper *helper)
{
	ft_putstr_fd("Error\n", 2);
	if (nb == 0)
		ft_putstr_fd("fork returns -1\n", 2);
	else if (nb == 1)
		ft_putstr_fd("pipe returns -1\n", 2);
	else if (nb == 2)
		ft_putstr_fd("dup2 returns -1\n", 2);
	else if (nb == 3)
		ft_putstr_fd("open returns -1\n", 2);
	else if (nb == 4)
		ft_putstr_fd("close returns -1\n", 2);
	else if (nb == 5)
		ft_putstr_fd("malloc error\n", 2);
	ft_free_struct_helper(helper);
	exit(1);
}
