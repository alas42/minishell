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
		return (NULL);
}

char	*get_line(t_infos *infos, int index)
{
	char	*line;

	if (!infos->envs)
		return (NULL);
	line = ft_strdup(infos->envs[index]);
	if (!line)
		return (NULL);
	return (line);
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
