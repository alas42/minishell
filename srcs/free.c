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
	t_cmd *cmd;
	t_cmd *next;

	cmd = infos->first_cmd;
	free(infos->line);
	while (cmd)
	{
		if (cmd->name_infile)
			free(cmd->name_infile);
		if (cmd->name_outfile)
			free(cmd->name_outfile);
		ft_free_tab_ptr(cmd->arg);
		cmd = cmd->next;
	}
	cmd = infos->first_cmd;
	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
