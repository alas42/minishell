/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:30:31 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 10:54:53 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_file_error(int state, t_cmd *cmd, t_infos *infos)
{
	char	*m;
	char	*cmd_name;
	char	*message;
	char	*tmp;
	int		len;

	m = ft_strdup("minishell: ");
	cmd_name = ft_strdup(cmd->arg[0]);
	if (state == 127)
		message = ft_strdup(" : No such file or directory");
	else
		message = ft_strdup(" : is a directory");
	len = ft_strlen(m) + ft_strlen(cmd_name) + ft_strlen(message);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	tmp[0] = '\0';
	tmp = ft_strcat(tmp, m);
	tmp = ft_strcat(tmp, cmd_name);
	tmp = ft_strcat(tmp, message);
	ft_putendl_fd(tmp, STDERR_FILENO);
	free_chars_bash_error(m, cmd_name, message, tmp);
	close_child_fd_error(cmd);
	free_infos(infos);
	exit(state);
}

int	ft_exists(char *file_path)
{
	struct stat	file_info;
	int			ret;

	ret = stat(file_path, &file_info);
	if (ret == 0)
		return (1);
	return (0);
}

int	is_a_directory(char *file_path)
{
	struct stat	file_info;
	int			ret;

	ret = stat(file_path, &file_info);
	if (ret == 0)
	{
		if (S_ISDIR(file_info.st_mode) == 1)
			return (1);
	}
	return (0);
}

void	check_errors_executable(char *file_path, t_cmd *cmd, t_infos *infos)
{
	size_t	len;

	len = ft_strlen(file_path);
	if (len == 1 && !ft_strncmp(".", file_path, 1))
		print_file_error(126, cmd, infos);
	if (len == 2 && !ft_strncmp("..", file_path, 2))
		print_file_error(126, cmd, infos);
	if (len >= 2 && !ft_strncmp("./", file_path, 2))
	{
		if (!ft_exists(file_path))
			print_file_error(127, cmd, infos);
		if (is_a_directory(file_path))
			print_file_error(126, cmd, infos);
	}
	else
	{
		if (!ft_exists(file_path))
			print_bash_error(127, cmd, infos);
	}
}
