/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:20:07 by avogt             #+#    #+#             */
/*   Updated: 2021/10/12 17:25:45 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_path(char *path_dir)
{
	ft_putendl_fd(path_dir, STDOUT_FILENO);
	if (path_dir)
		free(path_dir);
}

int	mini_pwd(t_infos *infos, t_cmd *cmd)
{
	char	*path_dir;
	size_t	length_path;

	length_path = 1024;
	path_dir = NULL;
	path_dir = getcwd(path_dir, length_path);
	while (errno == ERANGE)
	{
		length_path *= 2;
		path_dir = getcwd(path_dir, length_path);
		if (path_dir)
			break ;
	}
	if (!path_dir)
		return (1);
	print_path(path_dir);
	return (0);
	(void) infos;
	(void) cmd;
}
