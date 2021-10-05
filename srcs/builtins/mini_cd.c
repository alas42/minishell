/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:58 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:19:59 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*free_and_return(char *path_dir, char *ret)
{
	if (!ret)
	{
		if (path_dir)
			free(path_dir);
		return (NULL);
	}
	return (path_dir);
}

static char	*realloc_path_dir(char *path_dir, size_t *length_path)
{
	if (path_dir)
		free(path_dir);
	*length_path = *length_path * 2;
	path_dir = (char *)malloc(sizeof(char) * *length_path);
	if (!path_dir)
		return (NULL);
	return (path_dir);
}

static char	*get_actual_path(void)
{
	char	*path_dir;
	size_t	length_path;
	char	*ret;

	ret = 0;
	length_path = 1024;
	path_dir = (char *)malloc(sizeof(char) * length_path);
	if (!path_dir)
		return (NULL);
	ret = getcwd(path_dir, length_path);
	while (errno == ERANGE)
	{
		path_dir = realloc_path_dir(path_dir, &length_path);
		if (!path_dir)
			return (NULL);
		ret = getcwd(path_dir, length_path);
		if (ret)
			break ;
	}
	return (free_and_return(path_dir, ret));
}

int	mini_cd(t_infos *infos, t_cmd *cmd)
{
	char	*old_path;
	char	*current_path;
	char	*path;
	int		ret;
	int		ret_change_line[2];

	old_path = get_value(infos, "PWD");
	if (cmd->arg[1] == NULL)
		path = get_value(infos, "HOME");
	else
		path = cmd->arg[1];
	if (chdir(path))
		ret = 0;
	else
	{
		ret = 1;
		current_path = get_actual_path();
		ret_change_line[0] = change_line_env_tab(infos, "OLDPWD", old_path);
		ret_change_line[1] = change_line_env_tab(infos, "PWD", current_path);
		if (!ret_change_line[0] || !ret_change_line[1])
			ret = 0;
		free(current_path);
	}
	free(old_path);
	return (ret);
}
