#include "../../includes/minishell.h"

/*
** Checks if a file exist at the given path
** Returns 1 on success, 0 on failure
*/
int	ft_exists(char *file_path)
{
	struct stat file_info;
	int			ret;

	ret = stat(file_path, &file_info);
	if (ret == 0)
		return (1);
	return (0);
}

/*
** Add a given path to the first argument of the command
** Returns 1 on success, 0 on failure
*/
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

/*
**
** Find the index of env value 'to_find' in the environment list
** If not found, return -1
**
*/

int	find_pos_key(t_infos *infos, char *to_find)
{
	int	i;
	int j;
	int	len_to_find;

	len_to_find = 0;
	i = 0;
	if (!infos->envs)
		return (-1);
	while (infos->envs[i])
	{
		j = 0;
		len_to_find = ft_strlen(to_find);
		while (j < len_to_find)
		{
			if (infos->envs[i][j] != to_find[j])
				break ;
			j++;
			if (j == ft_strlen(to_find))
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
**
** (void functions are a no go, because there are errors that should be checked)
** This function add the execution path to every command in the chained list
** If it doesn't find, the path stays the same, it will try to execute it in the directory
**
*/

void	check_paths(t_infos *infos)
{
	int		i;
	int		ret_path;
	t_cmd	*cmd;

	cmd = infos->first_cmd;
	while (cmd)
	{
		i = 0;
		ret_path = 0;
		while (infos->paths[i])
		{
			if (ret_path != 1)
			{
				ret_path = add_path(cmd->arg, infos->paths[i],
					ft_strlen(infos->paths[i]));
			}
			i++;
		}
		cmd = cmd->next;
	}
}
