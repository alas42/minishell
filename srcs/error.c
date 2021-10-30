/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:27:46 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 17:47:46 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_stderr(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
}

void	print_error(int state, t_infos *infos)
{
	ft_putstr_fd("minishell: System function failed: ", STDERR_FILENO);
	if (state == E_MALLOC)
		ft_putendl_fd("Allocation error", STDERR_FILENO);
	else if (state == E_OPEN)
		ft_putendl_fd("Open error", STDERR_FILENO);
	else if (state == E_CLOSE)
		ft_putendl_fd("Close error", STDERR_FILENO);
	else if (state == E_FORK)
		ft_putendl_fd("Fork error", STDERR_FILENO);
	else if (state == E_PIPE)
		ft_putendl_fd("Pipe error", STDERR_FILENO);
	else if (state == E_DUP)
		ft_putendl_fd("Dup error", STDERR_FILENO);
	else if (state == E_DUP2)
		ft_putendl_fd("Dup2 error", STDERR_FILENO);
	else if (state == E_EXECVE)
		ft_putendl_fd("Execve error", STDERR_FILENO);
	set_error_code(1);
	free_infos(infos);
	exit(*get_error_code());
}

void	print_parsing_error(int state, t_infos *infos)
{
	if (infos->parse_error == 1)
		return ;
	else if (state == 1)
		print_stderr("minishell: Cannot find a closing quote (single')");
	else if (state == 2)
		print_stderr("minishell: Cannot find a closing quote (double\")");
	else if (state == 3)
		print_stderr("minishell: Error in closing the file");
	else if (state == 9)
		print_stderr("minishell: Error in Opening the infile");
	else if (state == 10)
		print_stderr("minishell: Error in Opening the outfile");
	infos->parse_error = 1;
	set_error_code(1);
}

static void	free_chars_bash_error(char *s, char *s1, char *s2, char *s3)
{
	free(s);
	free(s1);
	free(s2);
	free(s3);
}

static void	close_child_fd_error(t_cmd *cmd)
{
	if (cmd->fd_infile > -1)
		close(cmd->fd_infile);
	if (cmd->fd_outfile > -1)
		close(cmd->fd_outfile);
}

void	print_pipe_error(int state, t_cmd *cmd, t_infos *infos)
{
	if (infos->parse_error == 1)
		return ;
	if (state == 1)
		print_stderr("minishell: syntax error near unexpected token `|'");
	else if (state == 2)
		print_stderr("minishell: syntax error near unexpected token `>'");
	else if (state == 3)
		print_stderr("minishell: syntax error near unexpected token `<'");
	else if (state == 4)
		print_stderr("minishell: syntax error near unexpected token `newline`");	
	infos->parse_error = 1;
	set_error_code(2);
}

void	print_bash_error(int state, t_cmd *cmd)
{
	char	*m;
	char	*cmd_name;
	char	*message;
	char	*tmp;
	int		len;

	m = ft_strdup("minishell: ");
	cmd_name = ft_strdup(cmd->arg[0]);
	if (state == 127)
		message = ft_strdup(" : command not found");
	else if (state == 126)
		message = ft_strdup(" : command cannot be invoked");
	else
		message = ft_strdup(" : error");
	len = ft_strlen(m) + ft_strlen(cmd_name) + ft_strlen(message);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	tmp[0] = '\0';
	tmp = ft_strcat(tmp, m);
	tmp = ft_strcat(tmp, cmd_name);
	tmp = ft_strcat(tmp, message);
	ft_putendl_fd(tmp, STDERR_FILENO);
	free_chars_bash_error(m, cmd_name, message, tmp);
	close_child_fd_error(cmd);
	exit(state);
}
