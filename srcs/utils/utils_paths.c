/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:28 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 11:10:37 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	is_arg_rel_abs(t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->arg[0]);
	if (len > 0)
	{
		if (!ft_strcmp(".", cmd->arg[0]))
			return (1);
		else if (!ft_strcmp("..", cmd->arg[0]))
			return (1);
		if (!ft_strncmp(cmd->arg[0], "./", 2))
			return (1);
		else if (!ft_strncmp(cmd->arg[0], "/", 1))
			return (1);
	}
	return (0);
}

static void	add_path_cmds(t_infos *infos, t_cmd *cmd, char **paths)
{
	int	i;
	int	ret_path;

	ret_path = 0;
	i = 0;
	if (!is_arg_rel_abs(cmd))
	{
		while (paths[++i])
		{
			if (ret_path != 1)
				ret_path = add_path(cmd->arg, paths[i],
						ft_strlen(paths[i]));
			if (ret_path == -1)
				print_error(E_MALLOC, infos);
		}
	}
}

void	check_paths(t_infos *infos)
{
	t_cmd	*cmd;
	int		pos_path;
	char	*line_envp;
	char	**paths;

	pos_path = find_pos_key(infos, "PATH");
	if (pos_path == -1)
		return ;
	line_envp = get_line(infos, pos_path);
	paths = ft_split_char(line_envp, ':');
	cmd = infos->first_cmd;
	while (cmd)
	{
		add_path_cmds(infos, cmd, paths);
		cmd = cmd->next;
	}
	ft_free_tab_ptr(paths);
	free(line_envp);
}
