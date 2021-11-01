/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:13 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 00:24:19 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_here_doc_reading(t_cmd *cmd, int last)
{
	set_interruption(0);
	signal(SIGINT, here_doc_ctrl_c);
	rl_done = 0;
	if (last && cmd)
	{
		cmd->fd_infile = open("heredoc",
				O_TRUNC | O_WRONLY | O_CREAT, 0644);
	}
	return (0);
}

static int	end_here_doc_reading(t_cmd *cmd)
{
	close(cmd->fd_infile);
	cmd->fd_infile = open("heredoc", O_RDONLY, 0644);
	cmd->here_doc = 1;
	return (1);
}

static void	print_here_doc_error(void)
{
	ft_putstr_fd("minishell: warning :", STDERR_FILENO);
	ft_putendl_fd(" << here-doc >> ended with EOF", STDERR_FILENO);
}

int	here_doc_exec(char *str)
{
	char	*line;
	int		stop;

	stop = init_here_doc_reading(NULL, 0);
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
		free(line);
	}
	rl_event_hook = NULL;
	return (1);
}

int	last_here_doc(t_cmd *cmd, char *str)
{
	char	*line;
	int		stop;

	stop = init_here_doc_reading(cmd, 1);
	while (!stop)
	{
		rl_event_hook = check_for_ctrl_c;
		line = readline("> ");
		if (*get_interruption() == 1)
			rl_event_hook = NULL;
		if (rl_event_hook == NULL)
			return (0);
		if (!line)
		{
			print_here_doc_error();
			break ;
		}
		if (!(ft_strcmp(line, str)))
			stop = 1;
		else
			fd_write(cmd->fd_infile, line);
		free(line);
	}
	rl_event_hook = NULL;
	return (end_here_doc_reading(cmd));
}
