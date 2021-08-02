#include "../includes/minishell.h"

void	process_one(t_helper *helper, char **envp)
{
	int	ret_dup[2];

	if (close(helper->pipe[0]) == -1)
		ft_error_sysfunctions(4, helper);
	ret_dup[0] = dup2(helper->fd_infile, 0);
	ret_dup[1] = dup2(helper->pipe[1], 1);
	if (ret_dup[0] == -1 || ret_dup[1] == -1)
		ft_error_sysfunctions(2, helper);
	if (helper->process[0] == -1)
	{
		ft_free_struct_helper(helper);
		exit(1);
	}
	execve(helper->arg[0], helper->arg, envp);
	ft_putstr_fd(strerror(errno), 2);
	ft_free_struct_helper(helper);
	exit(1);
}

void	process_two(t_helper *helper, char **envp)
{
	int	ret_dup[2];

	ret_dup[0] = dup2(helper->pipe[0], 0);
	ret_dup[1] = dup2(helper->fd_outfile, 1);
	if (ret_dup[0] == -1 || ret_dup[1] == -1)
		ft_error_sysfunctions(2, helper);
	if (helper->process[1] == -1)
	{
		ft_free_struct_helper(helper);
		exit(1);
	}
	execve(helper->arg2[0], helper->arg2, envp);
	ft_putstr_fd(strerror(errno), 2);
	ft_free_struct_helper(helper);
	exit(1);
}

void	master_process(t_helper *helper, char **envp)
{
	pid_t	child;

	if (close(helper->pipe[1]) == -1)
		ft_error_sysfunctions(4, helper);
	child = fork();
	if (child == -1)
	{
		close(helper->pipe[1]);
		close(helper->pipe[0]);
		wait(NULL);
		ft_error_sysfunctions(0, helper);
	}
	else if (child == 0)
		process_two(helper, envp);
	else
	{
		if (close(helper->pipe[0]) == -1 || close(helper->fd_outfile) == -1)
			ft_error_sysfunctions(4, helper);
		wait(NULL);
		wait(NULL);
		ft_free_struct_helper(helper);
	}
}

int	exec_cmds(char **paths, char **cmds)
{
	pid_t		child;

	check_paths(cmds, paths);
	child = fork();
	if (child == -1)
		ft_putstr_fd(STDERR_FILENO, "Error returned by fork function");
	else if (child == 0)
		process_one(helper, envp);
	else
		master_process(helper, envp);
	return (0);
}
