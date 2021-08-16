#include "../../includes/minishell.h"

/*
**
** Create and returns a new string "key=value"
**
*/
char	*create_pair_key_value(char *key, char *value)
{
	char	*key_value_str;
	size_t	length;

	length = ft_strlen(key) + ft_strlen(value) + 4;
	key_value_str = (char *)malloc(sizeof(char) * (length));
	if (!key_value_str)
		return (NULL);
	key_value_str[0] = '\0';
	key_value_str = ft_strcat(key_value_str, key);
	key_value_str = ft_strcat(key_value_str, "=");
	key_value_str = ft_strcat(key_value_str, value);
	key_value_str = ft_strcat(key_value_str, "\0");
	return (key_value_str);
}

/*
** Calls create_pair_key_value and change the correct line to the new one
*/
int	change_line_env_tab(t_infos *infos, char *key, char *value)
{
	char	*key_value_str;
	int		ret_find_path;

	key_value_str = NULL;
	ret_find_path = find_pos_key(infos, key);
	if (ret_find_path > -1)
	{
		key_value_str = create_pair_key_value(key, value);
		if (!key_value_str)
			return (0);
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = key_value_str;
		return (1);
	}
	return (0);
}

/*
** Add a key_value pair to the envs tab
** Returns a copy from envs tab with an additional line
*/
char	**add_env_tab(char **envs, char *key_value_str)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	if (envs)
		while (envs[i])
			i++;
	new_tab = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	j = -1;
	while (++j < i - 1)
		new_tab[j] = ft_strdup(envs[j]);
	new_tab[j++] = ft_strdup(key_value_str);
	if (i != 0)
		new_tab[j++] = ft_strdup(envs[i - 1]);
	new_tab[j] = NULL;
	ft_free_tab_ptr(envs);
	return (new_tab);
}

/*
** Print the content of envs tab from infos if not NULL
*/
void	print_env_tab(t_infos *infos)
{
	int	i;

	i = 0;
	if (!infos->envs)
		return ;
	while (infos->envs[i])
	{
		ft_putendl_fd(infos->envs[i], STDOUT_FILENO);
		i++;
	}
}
