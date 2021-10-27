#include "../includes/minishell.h"

int	check_last_input_red(t_cmd *cmd, int pos)
{
	t_token	*red;
	int		i;

	i = 0;
	red = cmd->redirection;
	while (i++ < pos)
		red = red->next;
	while (red)
	{
		if (!(ft_strcmp(red->type, "here_doc"))
			|| !(ft_strcmp(red->type, "input_red")))
			return (red->pos);
		red = red->next;
	}
	return (0);
}

void	here_doc_exec(char *str)
{
	char	*line;

	while (get_next_line(1, &line) > 0)
	{
		if (!(ft_strcmp(line, str)))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	handle_here_doc(t_cmd *cmd, int pos)
{
	t_token	*red;
	int		ret;
	int		i;

	i = 0;
	ret = check_last_input_red(cmd, pos);
	red = cmd->redirection;
	while (i++ < pos && red)
		red = red->next;
	if (red == NULL || (ft_strcmp(red->type, "here_doc_word")))
		return ;
	if (ret == 0)
	{
		if (cmd->fd_infile > 0)
		{
			ret = close(cmd->fd_infile);
			if (ret < 0)
				printf("error in closing the file_des [%d] \n", cmd->fd_infile);
		}
		cmd->fd_infile = 1;
		printf("handle it in execution\n");
		return ;
	}
	here_doc_exec(red->content);
}

void	handle_infile(char *infile, char *type, t_cmd *cmd, int pos)
{
	int	i;

	i = -1;
	if (cmd->fd_infile > 0)
	{
		i = close(cmd->fd_infile);
		if (i < 0)
			printf("error in closing the file_des [%d] \n", cmd->fd_infile);
	}
	i = check_last_input_red(cmd, pos);
	cmd->fd_infile = open(infile, O_RDONLY, 0644);
	if (cmd->fd_infile < 0)
		printf("error in opening the file [%s] in mode [%s]\n", infile, type);
	 if (cmd->name_infile != NULL)
		free(cmd->name_infile);
	cmd->name_infile = ft_strdup(infile);
}

void	handle_outfile(char *outfile, char *type, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->fd_outfile > 0)
	{
		i = close(cmd->fd_outfile);
		if (i < 0)
			printf("error in closing the file_des [%d] \n", cmd->fd_outfile);
		if (cmd->name_outfile != NULL)
			free(cmd->name_outfile);
	}
	if (!(ft_strcmp(type, "output_red")))
		cmd->fd_outfile = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else
		cmd->fd_outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->fd_outfile < 0)
		printf("error in opening the file [%s] in mode [%s]\n", outfile, type);
	cmd->name_outfile = ft_strdup(outfile);
}
