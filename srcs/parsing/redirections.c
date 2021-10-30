#include "../includes/minishell.h"

int	handle_here_doc(t_cmd *cmd, int pos, t_infos *info)
{
	t_token	*red;
	int		ret;
	int		i;

	i = 0;
	ret = -1;
	ret = check_last_input_red(cmd, pos);
	red = cmd->redirection;
	while (i++ < pos && red)
		red = red->next;
	if (red == NULL || (ft_strcmp(red->type, "here_doc_word")))
		return (1);
	if (ret == 0)
	{
		if (cmd->fd_infile > 0)
		{
			ret = close(cmd->fd_infile);
			if (ret < 0)
				print_parsing_error(3, info);
		}
		return (last_here_doc(cmd, red->content));
	}
	return (here_doc_exec(red->content));
}

void	handle_infile(char *infile, t_cmd *cmd, int pos, t_infos *info)
{
	int	i;

	i = -1;
	if (cmd->fd_infile > 0)
	{
		i = close(cmd->fd_infile);
		if (i < 0)
			print_parsing_error(3, info);
	}
	i = check_last_input_red(cmd, pos);
	cmd->fd_infile = open(infile, O_RDONLY, 0644);
	if (cmd->fd_infile < 0)
		print_parsing_error(9, info);
	if (cmd->name_infile != NULL)
		free(cmd->name_infile);
	cmd->name_infile = ft_strdup(infile);
}

void	handle_outfile(char *outfile, char *type, t_cmd *cmd, t_infos *info)
{
	int	i;

	i = -1;
	if (cmd->fd_outfile > 0)
	{
		i = close(cmd->fd_outfile);
		if (i < 0)
			print_parsing_error(3, info);
		if (cmd->name_outfile != NULL)
			free(cmd->name_outfile);
	}
	if (!(ft_strcmp(type, "output_red")))
		cmd->fd_outfile = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else
		cmd->fd_outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->fd_outfile < 0)
		print_parsing_error(10, info);
	cmd->name_outfile = ft_strdup(outfile);
}

int	check_redirections(t_token *red, t_cmd *cmd, t_infos *info)
{
	if ((!(ft_strcmp(red->type, "output_red"))
			|| !(ft_strcmp(red->type, "double_output_red")))
		&& red->next != NULL && !ft_strcmp(red->next->type, "outfile"))
		handle_outfile(red->next->content, red->type, cmd, info);
	else if (!(ft_strcmp(red->type, "input_red")))
	{
		if (red->next != NULL && !ft_strcmp(red->next->type, "infile"))
			handle_infile(red->next->content, cmd, red->pos, info);
	}
	else if (!(ft_strcmp(red->type, "here_doc")))
	{
		if (!handle_here_doc(cmd, red->pos, info))
		{
			free_tokens(info);
			info->tokens = NULL;
			free_cmnds(info);
			info->commands = NULL;
			info->first_cmd = NULL;
			return (0);
		}
	}
	return (1);
}

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
			if (!check_redirections(red, cmd, info))
				return ;
			red = red->next;
		}
		cmd = cmd->next;
	}
}
