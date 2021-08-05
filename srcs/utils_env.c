#include "../includes/minishell.h"

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
	new_tab[j++] = key_value_str;
	new_tab[j++] = ft_strdup(envs[i - 1]);
	new_tab[j] = NULL;
	ft_free_tab_ptr(envs);
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
