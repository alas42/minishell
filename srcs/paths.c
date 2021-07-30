#include "../includes/minishell.h"

int	add_path(char **arg, char *path, int len_path)
{
	char	*new_str;
	int		i;
	int		c;

	i = -1;
	c = 0;
	new_str = NULL;
	new_str = (char *)malloc(sizeof(char) * (ft_len(arg[0]) + len_path + 2));
	if (!new_str)
		return (-1);
	while (path[++i] != '\0')
		new_str[i] = path[i];
	new_str[i++] = '/';
	while (arg[0][c] != '\0')
		new_str[i++] = arg[0][c++];
	new_str[i] = '\0';
/*
** if (!ft_exists(new_str))
** {
**	free(new_str);
**	return (0);
** }
*/
	free(arg[0]);
	arg[0] = new_str;
	return (1);
}

int	find_pos_path(char **envp, char *to_find)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (j < ft_len(to_find))
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

/*
void	check_paths(t_helper *helper)
{
	int	i;
	int	ret_path[2];

	i = 0;
	ret_path[0] = 0;
	ret_path[1] = 0;
	while (helper->paths[i])
	{
		if (ret_path[0] != 1)
			ret_path[0] = add_path(helper->arg, helper->paths[i],
					ft_len(helper->paths[i]));
		if (ret_path[0] == -1)
			ft_error_sysfunctions(5, helper);
		if (ret_path[1] != 1)
			ret_path[1] = add_path(helper->arg2, helper->paths[i],
					ft_len(helper->paths[i]));
		if (ret_path[1] == -1)
			ft_error_sysfunctions(5, helper);
		i++;
	}
	if (!ret_path[0])
		not_found(helper->arg[0], 0, 0, helper);
	if (!ret_path[1])
		not_found(helper->arg2[0], 1, 0, helper);
}
*/