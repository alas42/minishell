#include "../../includes/minishell.h"

void	handle_redirections(t_infos *info)
{
	t_cmd	*cmd;
	t_token	*red;

	cmd = info->commands;
	while (cmd)
	{
		red = cmd->redirection;
		while (red)
		{
			if ((!(ft_strcmp(red->type, "output_red"))
					|| !(ft_strcmp(red->type, "double_output_red")))
					&& red->next != NULL
					&& (!ft_strcmp(red->next->type, "outfile")))
				handle_outfile(red->next->content, red->type, cmd);
			else if (!(ft_strcmp(red->type, "input_red")))
			{
				if (red->next != NULL
					&& (!ft_strcmp(red->next->type, "infile")))
					handle_infile(red->next->content, red->type, cmd, red->pos);
			}
			else if (!(ft_strcmp(red->type, "here_doc")))
				handle_here_doc(cmd, red->pos);
			red = red->next;
		}
		cmd = cmd->next;
	}
}
