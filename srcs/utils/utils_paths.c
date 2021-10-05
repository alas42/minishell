/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:28 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:27:28 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exists(char *file_path)
{
	struct stat	file_info;
	int			ret;

	ret = stat(file_path, &file_info);
	if (ret == 0)
		return (1);
	return (0);
}

int	add_path(char **arg, char *path, int len_path)
{
	char	*new_str;
	int		i;
	int		c;

	i = -1;
	c = 0;
	new_str = NULL;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(arg[0]) + len_path + 2));
	if (!new_str)
		return (-1);
	while (path[++i] != '\0')
		new_str[i] = path[i];
	new_str[i++] = '/';
	while (arg[0][c] != '\0')
		new_str[i++] = arg[0][c++];
	new_str[i] = '\0';
	if (!ft_exists(new_str))
	{
		free(new_str);
		return (0);
	}
	free(arg[0]);
	arg[0] = new_str;
	return (1);
}

int	find_pos_key(t_infos *infos, char *to_find)
{
	int	i;
	int	j;
	int	len_to_find;

	len_to_find = 0;
	i = 0;
	if (!infos->envs)
		return (-1);
	while (infos->envs[i])
	{
		j = -1;
		len_to_find = ft_strlen(to_find);
		while (++j < len_to_find)
		{
			if (infos->envs[i][j] != to_find[j])
				break ;
			if (j + 1 == len_to_find)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	check_paths(t_infos *infos)
{
	int		i;
	int		ret_path;
	t_cmd	*cmd;

	if (!infos->paths)
		return ;
	cmd = infos->first_cmd;
	while (cmd)
	{
		i = -1;
		ret_path = 0;
		while (infos->paths[++i])
		{
			if (ret_path != 1)
				ret_path = add_path(cmd->arg, infos->paths[i],
						ft_strlen(infos->paths[i]));
			if (ret_path == -1)
				print_error(E_MALLOC, infos);
		}
		cmd = cmd->next;
	}
}
