#include "../../includes/minishell.h"

int	choose_builtin(t_infos *infos, t_cmd *cmd)
{
	int		i;
	char	*builtins_str[7];
	int		(*builtins[7])(t_infos *infos, t_cmd *cmd);

	builtins[B_UNSET] = mini_unset;
	builtins[B_ECHO] = mini_echo;
	builtins[B_PWD] = mini_pwd;
	builtins[B_EXPORT] = mini_export;
	builtins[B_CD] = mini_cd;
	builtins[B_EXIT] = mini_exit;
	builtins[B_ENV] = mini_env;
	builtins_str[B_UNSET] = "unset";
	builtins_str[B_ECHO] = "echo";
	builtins_str[B_CD] = "cd";
	builtins_str[B_ENV] = "env";
	builtins_str[B_EXIT] = "exit";
	builtins_str[B_EXPORT] = "export";
	builtins_str[B_PWD] = "pwd";
	i = -1;
	while (++i <= B_UNSET)
		if (!ft_strcmp(builtins_str[i], cmd->arg[0]))
			return ((*builtins[i])(infos, cmd));
	return (-1);
}

/*
**
** A Recursiv function that executes the commands :
** creating child processes &&
** setting the pipes and correct fds
**
** DIDNT DO THE >>  and << because I don't really understands
**(for now) how it is working
**
*/

static void	piping(t_infos *infos)
{
	if (infos->index_cmd % 2)
	{
		if (pipe(infos->pipe_a) == -1)
			print_error(E_PIPE, infos);
	}
	else
	{
		if (pipe(infos->pipe_b) == -1)
			print_error(E_PIPE, infos);
	}
}

static void	child_process(t_infos *infos, t_cmd *cmd, char **envp)
{
	int	ret;

	ret = 0;
	if (child_fds(infos, cmd))
	{
		ft_putendl_fd("close or dup2 error in child", STDERR_FILENO);
	}
	if (cmd->builtin)
	{
		ret = choose_builtin(infos, cmd);
	}
	else if (!cmd->builtin || ret == -1)
	{
		execve(cmd->arg[0], cmd->arg, envp);
		print_error(E_EXECVE, infos);
	}
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
	int		process_id;

	cmd = get_cmd(infos);
	if (!cmd)
		return (1);
	piping(infos);
	process_id = fork();
	if (process_id == 0)
		child_process(infos, cmd, envp);
	else if (process_id == -1)
		print_error(E_FORK, infos);
	else
		parent_process(infos, cmd, envp);
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
	char	**cmd1;
	char	**cmd2;
	char	**cmd3;
	char	**cmd4;
	t_cmd	*cmd01;
	t_cmd	*cmd02;
	t_cmd	*cmd03;
	t_cmd	*cmd04;
	int		stdout_save;
	int		stdin_save;

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
