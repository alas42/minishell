#include "../includes/minishell.h"

int    check_last_input_red(t_cmd *cmd, int pos)
{
	t_token *red;
	int     i;

	i = 0;
	red = cmd->redirection;
	while (i++ < pos)
		red = red->next;
	while (red)
	{
		if (!(ft_strcmp(red->type, "here_doc")) || !(ft_strcmp(red->type, "input_red")))
			return (red->pos);
		red = red->next;
	}
	return (0);
}

void    here_doc_exec(char *str)
{
	char    *line;
	int     i;

	i = -1;
	while ((i = get_next_line(1, &line)) > 0)
	{
		if (!(ft_strcmp(line, str)))
		{
			free(line);
			break;
		}
		free(line);
	}
}

int		fd_write(int fd, char *line)
{
	int		i;
	int		nl;

	nl = 10;
	i = 0;
	while(line[i])
	{
		write(fd, &line[i], 1);
		i++;
	}
	write(fd, &nl, 1);
	return (i);
}
