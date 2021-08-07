#include "../includes/minishell.h"

void	ft_free_tab_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}

void	free_infos(t_infos *infos)
{
	free(infos->line);
	ft_free_tab_ptr(infos->paths);
	ft_free_tab_ptr(infos->envs);
	free_env_list(infos);
	free_cmd_list(infos);
}
