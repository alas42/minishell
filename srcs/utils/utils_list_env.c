#include "../../includes/minishell.h"

char	*get_pair(t_infos *infos, int index)
{
	t_env	*env;
	int		i;

	i = 0;
	env = infos->first_env;
	while (i++ < index)
		env = env->next;
	return (env->pair);
}

void	add_env(t_infos *infos, t_env *new)
{
	t_env *tmp;

	tmp = infos->first_env;
	new->next = NULL;
	if (tmp == NULL)
	{
		infos->first_env = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*creating_env(char *str)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->pair = ft_strdup(str);
	env->order = 0;
	env->next = NULL;
	return (env);
}

void	get_env_list(t_infos *infos, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		add_env(infos, creating_env(envp[i]));
		i++;
	}
}

void	free_env_list(t_infos *infos)
{
	t_env	*env;
	t_env	*tmp;

	env = infos->first_env;
	while (env)
	{
		tmp = env;
		free(env->pair);
		env = env->next;
		free(tmp);
	}
}
