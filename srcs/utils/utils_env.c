#include "../../includes/minishell.h"

/*
**
** Create a string "key=value" and replace them if key is already in **env
** Returns 0 if failed to find the key
** Returns 1 on success
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

int	change_line_env_tab(t_infos *infos, char *key,  char *value)
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

char	**add_env_tab(char **envs, char *key_value_str)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	while (envs[i])
	{
		i++;
	}
	new_tab = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	j = 0;
	while (j < i - 1)
	{
		new_tab[j] = ft_strdup(envs[j]);
		j++;
	}
	new_tab[j++] = ft_strdup(key_value_str);
	new_tab[j++] = ft_strdup(envs[i - 1]);
	new_tab[j] = NULL;
	ft_free_tab_ptr(envs);
	return (new_tab);
}

char	**remove_env_tab(t_infos *infos, char *key)
{
	int		i;
	int		j;
	char	**new_tab;
	int		pos_key;

	i = 0;
	while (infos->envs[i])
		i++;
	new_tab = (char **)malloc(sizeof(char *) * i);
	if (!new_tab)
		return (NULL);
	pos_key = find_pos_key(infos, key);
	j = 0;
	while (j < i)
	{
		if (j < pos_key)
			new_tab[j] = ft_strdup(infos->envs[j]);
		else if (j > pos_key)
			new_tab[j - 1] = ft_strdup(infos->envs[j]);
		j++;
	}
	new_tab[i] = NULL;
	ft_free_tab_ptr(infos->envs);
	return (new_tab);
}

char	**get_env_tab(char **envp)
{
	char	**envs;
	int		i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	envs = (char **)malloc(sizeof(char *) *(i + 1));
	if (!envs)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envs[i] = ft_strdup(envp[i]);
		i++;
	}
	envs[i] = NULL;
	return (envs);
}

void	print_env_tab(t_infos *infos)
{
	int	i;

	i = 0;
	while (infos->envs[i])
	{
		ft_putendl_fd(infos->envs[i], STDOUT_FILENO);
		i++;
	}
}
