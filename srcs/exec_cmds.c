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
*/

static void	check_content(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		ft_putendl_fd(cmd[i++], 1);
}

/*
**
** returns the t_cmd node thank to the integer infos->nb_cmd
**
*/

t_cmd	*get_cmd(t_infos *infos)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = infos->first;
	while (i < infos->nb_cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

/*
**
** A Recursiv function that executes the commands :
** creating child processes &&
** setting the pipes and correct fds
**
*/

int	exec_cmds(t_infos *infos, char **envp)
{
	t_cmd	*cmd;
	int		fork_ret;

	cmd = get_cmd(infos);
	if (cmd)
		check_content(cmd->arg);
	if (cmd) // check if the cmd exists or at the end of list
	{
		fork_ret = fork();
		if (fork_ret == 0) //no error checking yet
		{
			if (cmd->name_infile)
			{
				close(infos->pipe[0]);
				cmd->fd_infile = open(cmd->name_infile, O_RDONLY, 0644);
				dup2(cmd->fd_infile, STDIN_FILENO);
			}
			else if (cmd->pipe_in)
			{
				dup2(infos->pipe[0], STDIN_FILENO);
			}
			else
				close(infos->pipe[0]);
			if (cmd->name_outfile)
			{
				close(infos->pipe[1]);
				cmd->fd_outfile = open(cmd->name_outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
				dup2(cmd->fd_outfile, STDOUT_FILENO);
			}
			else if (cmd->pipe_out)
			{
				dup2(infos->pipe[1], STDOUT_FILENO);
			}
			else
				close(infos->pipe[1]);
			execve(cmd->arg[0], cmd->arg, envp);
		}
		else
		{
			infos->nb_cmd = infos->nb_cmd + 1;
			close(infos->pipe[1]);
			exec_cmds(infos, envp);
			close(infos->pipe[0]);
			wait(NULL);
		}
	}
	return (1);
}

/*
**
** To be removed
** Because there is no parsing yet
** Creating nodes and adding them to the list
**
*/

static void	add_cmd(char **arg, t_infos *infos, int pipe_in, int pipe_out)
{
	t_cmd *cmd;
	t_cmd *tmp;

	tmp = infos->first;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->arg = arg;
	cmd->pipe_in = pipe_in;
	cmd->pipe_out = pipe_out;
	cmd->name_infile = NULL;
	cmd->name_outfile = NULL;
	cmd->builtin = 0;
	cmd->process = 1;
	cmd->next = NULL;
	if (tmp == NULL)
	{
		cmd->prec = NULL;
		infos->first = cmd;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		cmd->prec = tmp;
		tmp->next = cmd;
	}
}

/*
**
** To be removed
** Because there is no parsing yet
** Creating commands
**
*/

void	tests_exec_cmds(t_infos *infos, char **envp) //there will be plenty of bugs with the fds
{
	char **cmd1;
	char **cmd2;
	char **cmd3;

	cmd1 = ft_split_char("ls -l", ' ');
	cmd2 = ft_split_char("grep a", ' ');
	cmd3 = ft_split_char("wc -c", ' ');
	add_cmd(cmd1, infos, 0, 1);
	add_cmd(cmd2, infos, 1, 1);
	add_cmd(cmd3, infos, 1, 0);
	check_paths(infos);
	exec_cmds(infos, envp);
}
