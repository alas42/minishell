#include "../../includes/minishell.h"

char	*get_key(t_infos *infos, int index)
{
	int		i;
	char	*key;

	i = 0;
	if (!infos->envs || !infos->envs[index])
		return (NULL);
	while (infos->envs[index][i] != '\0' && infos->envs[index][i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (infos->envs[index][i] != '\0' && infos->envs[index][i] != '=')
	{
		key[i] = infos->envs[index][i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

/*
** Returns the value in a char * corresponding to the key in infos->envs
*/
char	*get_value(t_infos *infos, char *key)
{
	int		index;
	int		i;
	int		counter;
	char	*value;
	size_t	len_value;

	index = find_pos_key(infos, key);
	if (index == -1)
		return (NULL);
	len_value = ft_strlen(infos->envs[index]) - (ft_strlen(key) + 1);
	counter = ft_strlen(key) + 1;
	if (len_value > 0)
	{
		value = (char *)malloc(sizeof(char) * (len_value + 1));
		if (!value)
			return (NULL);
		i = 0;
		while (infos->envs[index][counter] != '\0')
			value[i++] = infos->envs[index][counter++];
		value[i] = '\0';
		return (value);
	}
	else
		return(NULL);
}

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

/*
** Remove an entry from envs tab
** - Returns a copy from initial tab without the line wanted to be removed
** - Returns the original tab as is if the key isn't found
*/
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
	if (pos_key == -1)
	{
		ft_free_tab_ptr(new_tab);
		return (infos->envs);
	}
	j = -1;
	while (++j < i)
	{
		if (j < pos_key)
			new_tab[j] = ft_strdup(infos->envs[j]);
		else if (j > pos_key)
			new_tab[j - 1] = ft_strdup(infos->envs[j]);
	}
	new_tab[i] = NULL;
	ft_free_tab_ptr(infos->envs);
	return (new_tab);
}

/*
** Makes a copy from **envp to infos->envs
** Returns NULL if **envp is NULL
*/
char	**get_env_tab(char **envp)
{
	char	**envs;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
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
	ft_putendl_fd("\n", STDOUT_FILENO);
}
