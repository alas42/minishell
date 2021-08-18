#include "../../includes/minishell.h"

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
**
*/
/*
** Remove an entry from envs tab
** - Returns a copy from initial tab without the line wanted to be removed
** - Returns the original tab as is if the key isn't found
*/
static char	**copy_new_tab(t_infos *infos, int pos_key, char **new_tab)
{
	int	i;

	i = -1;
	while (infos->envs[++i])
	{
		if (i < pos_key)
		{
			new_tab[i] = ft_strdup(infos->envs[i]);
			if (!new_tab[i])
			{
				ft_free_tab_ptr(new_tab);
				return (NULL);
			}
		}
		else if (i > pos_key)
		{
			new_tab[i - 1] = ft_strdup(infos->envs[i]);
			if (!new_tab[i - 1])
			{
				ft_free_tab_ptr(new_tab);
				return (NULL);
			}
		}
	}
	return (new_tab);
}

char	**remove_env_tab(t_infos *infos, char *key)
{
	int		i;
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
	new_tab = copy_new_tab(infos, pos_key, new_tab);
	if (!new_tab)
		return (NULL);
	new_tab[i - 1] = NULL;
	ft_free_tab_ptr(infos->envs);
	return (new_tab);
}

int	mini_unset(t_infos *infos, t_cmd *cmd)
{
	if (infos->envs)
	{
		infos->envs = remove_env_tab(infos, cmd->arg[1]);
		if (!infos->envs)
			print_error(E_MALLOC, infos);
	}
	return (1);
}

/*
void	test_unset(t_infos *infos)
{
	mini_unset(infos, "test_key");
	mini_unset(infos, "testare_key");
	print_env_tab(infos);
}
*/
