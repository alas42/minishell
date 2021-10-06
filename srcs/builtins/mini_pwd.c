/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:20:07 by avogt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/05 23:20:16 by yassharm         ###   ########.fr       */
=======
/*   Updated: 2021/10/06 18:07:55 by avogt            ###   ########.fr       */
>>>>>>> aacf8483cd7f6ae8de6435397f71f59f08e2add6
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_path(char *path_dir)
{
	(void)cmd;
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
		return (-1);
	print_path(path_dir);
	return (0);
	(void) infos;
	(void) cmd;
}
