#include "../../includes/minishell.h"

static int	is_builtin(char **arg)
{
	int		i;
	char	*builtins_str[6];

	builtins_str[B_UNSET] = "unset";
	builtins_str[B_ECHO] = "echo";
	builtins_str[B_CD] = "cd";
	builtins_str[B_ENV] = "env";
	builtins_str[B_EXIT] = "exit";
	builtins_str[B_EXPORT] = "export";
	builtins_str[B_PWD] = "pwd";
	i = 0;
	while (i <= B_UNSET)
	{
		if (!strcmp(builtins_str[i], arg[0]))
			return (i);
		i++;
	}
	return (-1);
}

/*
**
** A Recursiv function that executes the commands :
** creating child processes &&
** setting the pipes and correct fds
**
** DIDNT DO THE >>  and << because I don't really understands (for now) how it is working
**
*/

static int	piping(t_infos *infos)
{
	int	ret_pipe;

	ret_pipe = 0;
	if (infos->index_cmd % 2)
		pipe(infos->pipe_a);
	else
		pipe(infos->pipe_b);
	if (ret_pipe > -1)
		return (0);
	return (1);
}

static void	child_process(t_infos *infos, t_cmd *cmd, char **envp)
{
	if (child_fds(infos, cmd))
	{
		ft_putendl_fd("close or dup2 error in child", STDERR_FILENO);
	}
	if (is_builtin(cmd->arg) > -1)
	{
		ft_putendl_fd("NOT AN ERROR : the cmd is a builtin", STDERR_FILENO);
	}
	execve(cmd->arg[0], cmd->arg, envp);
	ft_putendl_fd("execve error", STDERR_FILENO);
}

static void	parent_process(t_infos *infos, t_cmd *cmd, char **envp)
{
	if (parent_fds(infos, cmd))
	{
		ft_putendl_fd("close error in parent", STDERR_FILENO);
	}
	infos->index_cmd = infos->index_cmd + 1;
	exec_cmds(infos, envp);
	wait(NULL);
}

int	exec_cmds(t_infos *infos, char **envp)
{
	t_cmd	*cmd;
	int		fork_ret;

	cmd = get_cmd(infos);
	if (cmd)
	{
		if (piping(infos))
		{
			ft_putendl_fd("error in pipe() function", STDERR_FILENO);
		}
		fork_ret = fork();
		if (fork_ret == 0)
		{
			child_process(infos, cmd, envp);
		}
		else if (fork_ret == -1)
		{
			ft_putendl_fd("error in fork() function", STDERR_FILENO);
		}
		else
		{
			parent_process(infos, cmd, envp);
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
*/

void	tests_exec_cmds(t_infos *infos, char **envp)
{
	char **cmd1;
	char **cmd2;
	char **cmd3;
	char **cmd4;
	t_cmd *cmd01;
	t_cmd *cmd02;
	t_cmd *cmd03;
	t_cmd *cmd04;
	int		stdout_save, stdin_save;

	cmd1 = ft_split_char("ls -l", ' ');
	cmd2 = ft_split_char("grep a", ' ');
	cmd3 = ft_split_char("grep r", ' ');
	cmd4 = ft_split_char("wc", ' ');
	cmd01 = creating_cmd(cmd1, 0, 1);
	cmd02 = creating_cmd(cmd2, 1, 1);
	cmd03 = creating_cmd(cmd3, 1, 1);
	cmd04 = creating_cmd(cmd4, 1, 0);
	add_cmd(infos, cmd01);
	add_cmd(infos, cmd02);
	add_cmd(infos, cmd03);
	add_cmd(infos, cmd04);
	check_paths(infos);
	stdout_save = dup(STDOUT_FILENO);
	stdin_save = dup(STDIN_FILENO);
	exec_cmds(infos, envp);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
}
