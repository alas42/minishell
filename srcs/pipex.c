/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:46:30 by avogt             #+#    #+#             */
/*   Updated: 2021/07/30 16:50:50 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

t_helper	*init_helper(char *av[], char **envp)
{
	t_helper	*helper;

	helper = (t_helper *)malloc(sizeof(t_helper));
	if (!helper)
		ft_error_sysfunctions(5, helper);
	helper->process[0] = 1;
	helper->process[1] = 1;
	helper->arg = ft_parsed_cmd(av[2], ' ');
	helper->arg2 = ft_parsed_cmd(av[3], ' ');
	if (helper->arg == NULL || helper->arg2 == NULL)
		ft_error_functions(0, helper);
	helper->pos_path = find_pos_path(envp, "PATH");
	if (helper->pos_path == -1)
		ft_error_functions(1, helper);
	helper->paths = ft_parsed_cmd(&envp[helper->pos_path][5], ':');
	if (ft_exists(av[1]))
		helper->fd_infile = open(av[1], O_RDONLY, 0644);
	else
		not_found(av[1], 0, 1, helper);
	helper->fd_outfile = open(av[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (helper->fd_infile == -1 || helper->fd_outfile == -1)
		ft_error_sysfunctions(3, helper);
	if (pipe(helper->pipe) == -1)
		ft_error_sysfunctions(1, helper);
	return (helper);
}

int	main(int ac, char *av[], char **envp)
{
	pid_t		child;
	t_helper	*helper;

	if (ac != 5)
		ft_usage();
	helper = init_helper(av, envp);
	check_paths(helper);
	child = fork();
	if (child == -1)
		ft_error_sysfunctions(0, helper);
	else if (child == 0)
		process_one(helper, envp);
	else
		master_process(helper, envp);
	return (0);
}
