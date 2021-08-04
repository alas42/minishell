#include "../includes/minishell.h"

/*
**
** no checking for errors for now (there is plenty to do)
**
** basic algo, created for:
** checking what needs to be parsed &&
** settings to be added in the structures
**
*/

/*
**
** to be removed, checks the content of **args in a t_cmd
**


static void	check_content(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		ft_putendl_fd(cmd[i++], 1);
}
*/

/*
**
** A Recursiv function that executes the commands :
** creating child processes &&
** setting the pipes and correct fds
**
** DIDNT DO THE >>  and << because I don't really understands (for now) how it is working
**
*/

int	open_fds(t_infos *infos, t_cmd *cmd)
{
	if (infos->index_cmd == 0)
	{
		if (cmd->name_infile != NULL)
		{
			cmd->fd_infile = open(cmd->name_infile, O_RDONLY, 0644);
			dup2(cmd->fd_infile, STDIN_FILENO);
		}
		if (infos->nb_pipe > 0)
			dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
		if (cmd->name_outfile != NULL)
		{
			cmd->fd_outfile = open(cmd->name_outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
			dup2(cmd->fd_outfile, STDOUT_FILENO);
		}
	}
	else if (infos->index_cmd == infos->nb_pipe)
	{
		if (infos->index_cmd % 2)
			dup2(infos->pipe_b[READ], STDIN_FILENO);
		else
			dup2(infos->pipe_a[READ], STDIN_FILENO);
		if (cmd->name_outfile != NULL)
		{
			cmd->fd_outfile = open(cmd->name_outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
			dup2(cmd->fd_outfile, STDOUT_FILENO);
		}
	}
	else
	{
		if (infos->index_cmd % 2)
		{
			dup2(infos->pipe_b[READ], STDIN_FILENO);
			dup2(infos->pipe_a[WRITE], STDOUT_FILENO);
		}
		else
		{
			dup2(infos->pipe_a[READ], STDIN_FILENO);
			dup2(infos->pipe_b[WRITE], STDOUT_FILENO);
		}
	}
	return (1);
}

int	close_fds(t_infos *infos, t_cmd *cmd)
{
	if (infos->index_cmd == 0)
	{
		if (cmd->name_infile != NULL)
		{
			close(cmd->fd_infile);
			dup(STDIN_FILENO);
		}
		if (infos->nb_pipe > 0)
			close(infos->pipe_b[WRITE]);
		if (cmd->name_outfile != NULL)
		{
			close(cmd->fd_outfile);
		}
	}
	else if (infos->index_cmd == infos->nb_pipe)
	{
		if (infos->index_cmd % 2)
			close(infos->pipe_b[READ]);
		else
			close(infos->pipe_a[READ]);
		if (cmd->name_outfile != NULL)
			close(cmd->fd_outfile);
	}
	else
	{
		if (infos->index_cmd % 2)
		{
			close(infos->pipe_b[READ]);
			close(infos->pipe_a[WRITE]);
		}
		else
		{
			close(infos->pipe_a[READ]);
			close(infos->pipe_b[WRITE]);
		}
	}
	return (1);
}

int	exec_cmds(t_infos *infos, char **envp)
{
	t_cmd	*cmd;
	int		fork_ret;

	cmd = get_cmd(infos);
	if (cmd) // check if the cmd exists or at the end of list
	{
		if (infos->index_cmd % 2)
			pipe(infos->pipe_a);
		else if (infos->nb_pipe != 0)
			pipe(infos->pipe_b);
		if (!open_fds(infos, cmd)) // No error checking yet
			return (0);
		fork_ret = fork();
		if (fork_ret == 0) //no error checking yet
		{
			execve(cmd->arg[0], cmd->arg, envp);
		}
		else
		{
			if (!close_fds(infos, cmd))
				return (0);
			infos->index_cmd = infos->index_cmd + 1;
			exec_cmds(infos, envp);// no error checking yet
			wait(NULL);
		}
	}
	return (1);
}

/*
**
** To be removed
** Because there is no parsing yet
** Creating commands
**
** BUG 1: the last fd when not stdout, change the fd from terminal, thus in main isatty() will return 0 and exits
** BUG 2: the last fd when stdout, don't close itslef, because then again, it will close the fd from terminal
**
*/

void	tests_exec_cmds(t_infos *infos, char **envp) //there will be plenty of bugs with the fds
{
	char **cmd1;
	char **cmd2;
	char **cmd3;
	t_cmd *cmd01;
	t_cmd *cmd02;
	t_cmd *cmd03;

	cmd1 = ft_split_char("ls -l", ' ');
	cmd2 = ft_split_char("grep a", ' ');
	cmd3 = ft_split_char("wc -c", ' ');
	cmd01 = creating_cmd(cmd1, 0, 0);
	cmd02 = creating_cmd(cmd2, 1, 1);
	cmd03 = creating_cmd(cmd3, 1, 0);
	cmd01->name_infile = ft_strdup("infile_test");
	//cmd03->name_outfile = ft_strdup("outfile_test");
	add_cmd(infos, cmd01);
	add_cmd(infos, cmd02);
	add_cmd(infos, cmd03);
	check_paths(infos);
	exec_cmds(infos, envp);
}
