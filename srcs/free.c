#include "../includes/minishell.h"

void	ft_free_tab_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_infos(t_infos *infos)
{
	t_cmd *cmd;
	t_cmd *next;

	cmd = infos->first;
	free(infos->line);
	while (cmd)
	{
		ft_free_tab_ptr(cmd->arg);
		cmd = cmd->next;
	}
	cmd = infos->first;
	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
