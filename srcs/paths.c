#include "../includes/minishell.h"

int	ft_exists(char *file_path)
{
	struct stat file_info;
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

int	find_pos_path(char **envp, char *to_find)
{
	int	i;
	int	j;
	int	len_to_find;

	j = 0;
	i = 0;
	len_to_find = 0;
	while (envp[i])
	{
		j = 0;
		len_to_find = ft_strlen(to_find);
		while (j < len_to_find)
		{
			if (envp[i][j] != to_find[j])
				break ;
			j++;
			if (j == 4)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	check_paths(char **paths, char **arg)
{
	int	i;
	int	ret_path;

	i = 0;
	ret_path = 0;
	while (paths[i])
	{
		if (ret_path != 1)
		{
			ret_path = add_path(arg, paths[i], ft_strlen(paths[i]));
			break ;
		}
		i++;
	}
}
