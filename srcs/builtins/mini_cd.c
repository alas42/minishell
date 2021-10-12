/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:58 by avogt             #+#    #+#             */
/*   Updated: 2021/10/12 17:24:49 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_actual_path(void)
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
		return (NULL);
	return (path_dir);
}

static int	change_lines(t_infos *infos, char *old, char *cur, char *path)
{
	int	ret_change_line[2];
	int	ret;

	ret_change_line[0] = change_line_env_tab(infos, "OLDPWD", old);
	ret_change_line[1] = change_line_env_tab(infos, "PWD", cur);
	ret = 0;
	if (!ret_change_line[0] || !ret_change_line[1])
		ret = 1;
	if (cur)
		free(cur);
	if (path)
		free(path);
	if (old)
		free(old);
	return (ret);
}

int	mini_cd(t_infos *infos, t_cmd *cmd)
{
	char	*old_path;
	char	*current_path;
	char	*path;
	int		ret;

	old_path = get_value(infos, "PWD");
	if (cmd->arg[1] == NULL)
		path = get_value(infos, "HOME");
	else
		path = ft_strdup(cmd->arg[1]);
	if (!old_path || !path || chdir(path))
		return(1);
	ret = 0;
	current_path = get_actual_path();
	if (!current_path)
	{
		if (path)
			free(path);
		if (old_path)
			free(old_path);
		return (1);
	}
	ret = change_lines(infos, old_path, current_path, path);
	return (ret);
}
