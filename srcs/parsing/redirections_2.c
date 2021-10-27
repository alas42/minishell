#include "../../includes/minishell.h"

void	handle_redirections(t_infos *info)
{
	t_cmd	*cmd;
	t_token	*r;

	cmd = info->commands;
	while (cmd)
	{
		r = cmd->redirection;
		while (r)
		{
			if ((!(ft_strcmp(r->type, "output_red"))
					|| !(ft_strcmp(r->type, "double_output_red")))
				&& r->next != NULL && (!ft_strcmp(r->next->type, "outfile")))
				handle_outfile(r->next->content, r->type, cmd);
			else if (!(ft_strcmp(r->type, "input_red")))
			{
				if (r->next != NULL
					&& (!ft_strcmp(r->next->type, "infile")))
					handle_infile(r->next->content, r->type, cmd, r->pos);
			}
			else if (!(ft_strcmp(r->type, "here_doc")))
				handle_here_doc(cmd, r->pos);
			r = r->next;
		}
		cmd = cmd->next;
	}
}
