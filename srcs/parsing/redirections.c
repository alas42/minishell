#include "../includes/minishell.h"

static int	*get_interruption(void)
{
	static int	status = 0;

	return (&status);
}

static void	set_interruption(int status)
{
	*get_interruption() = status;
}


int	here_doc_exec(char *str)
{
	char	*line;
	int		stop;

	stop = 0;
	while (!stop)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning :", STDERR_FILENO);
			ft_putendl_fd(" << here-doc >> ended with EOF", STDERR_FILENO);
			break ;
		}
		// printf("%d\n", *get_not_global_but_static());
		if (*get_not_global_but_static() == 130)
		{
			return (0);
		}
		if (!(ft_strcmp(line, str)))
			stop = 1;
		free(line);
	}
	return (1);
}

void	here_doc_ctrl_c(int status)
{
	int	code;

	code = 130;
	set_not_global_but_static(code);
	set_interruption(1);
	(void)status;
}

int	check_for_ctrl_c(void)
{
	if (*get_interruption() == 1 && rl_done == 0)
		rl_done = 1;
	else
		rl_done = 0;
	return (0);
}

int	last_here_doc(t_cmd *cmd, char *str)
{
	char	*line;
	int		stop;

	stop = 0;
	set_interruption(0);
	cmd->fd_infile = open("here_doc_f", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	signal(SIGINT, here_doc_ctrl_c);
	rl_done = 0;
	while (!stop)
	{
		rl_event_hook = check_for_ctrl_c;
		line = readline("> ");
		if (*get_interruption() == 1)
		{
			rl_event_hook = NULL;
			return (0);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning :", STDERR_FILENO);
			ft_putendl_fd(" << here-doc >> ended with EOF", STDERR_FILENO);
			break ;
		}
		if (!(ft_strcmp(line, str)))
			stop = 1;
		else
			fd_write(cmd->fd_infile, line);
		free(line);
	}
	rl_event_hook = NULL;
	close(cmd->fd_infile);
	cmd->fd_infile = open("here_doc_f", O_RDONLY, 0644);
	cmd->here_doc = 1;
	return (1);
}

int	handle_here_doc(t_cmd *cmd, int pos)
{
	t_token     *red;
	int         ret;
	int         i;

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
				printf("error in closing the file_des [%d] \n", cmd->fd_infile);
		}
		return (last_here_doc(cmd, red->content));
	}
	return (here_doc_exec(red->content));
}

void    handle_infile(char *infile, char *type, t_cmd *cmd, int pos)
{
	int i;

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

void    handle_outfile(char *outfile, char *type, t_cmd *cmd)
{
	int i;

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

void	handle_redirections(t_infos *info)
{
	t_cmd	*cmd;
	t_token *red;

	cmd = info->commands;
	while(cmd)
	{
		red = cmd->redirection;
		while (red)
		{
			if ((!(ft_strcmp(red->type, "output_red"))
			|| !(ft_strcmp(red->type, "double_output_red")))
			&& red->next != NULL && (!ft_strcmp(red->next->type, "outfile")))
					handle_outfile(red->next->content, red->type, cmd);
			else if (!(ft_strcmp(red->type, "input_red")))
			{
				if (red->next != NULL && (!ft_strcmp(red->next->type, "infile")))
					handle_infile(red->next->content, red->type, cmd, red->pos);
			}
			else if (!(ft_strcmp(red->type, "here_doc")))
			{
				if (!handle_here_doc(cmd, red->pos))
				{
					free_tokens(info);
					info->tokens = NULL;
					return ;
				}
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
}
