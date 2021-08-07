#include "../includes/minishell.h"

int	exec_cmds2(t_infos *infos, char **envp)
{
	t_cmd	*cmd;
	int		fork_ret;
	int		i;

	i = 0;
	while (i < infos->nb_cmd) // check if the cmd exists or at the end of list
	{
		cmd = get_cmd(infos);
		fork_ret = fork();
		if (fork_ret == 0) // CHILD
		{
			execve(cmd->arg[0], cmd->arg, envp);
		}
		else // PARENT
		{
			infos->index_cmd = infos->index_cmd + 1;
		}
		i++;
	}
	i = 0;
	while (i++ < infos->nb_cmd)
		wait(NULL);
	return (1);
}

/*
**
** To be removed
** Because there is no parsing yet
** Creating commands
**
** BUG 1: the last fd when not stdout, change the fd from terminal, thus in main isatty() will return 0 and exits
** RESOLVED : saved the stdin and out and restore them after all function were executed.
** 
** BUG 2: the last fd when stdout, don't close itslef, because then again, it will close the fd from terminal
** DONT KNOW WHAT TO DO
*/

void	tests_exec_cmds2(t_infos *infos, char **envp) //there will be plenty of bugs with the fds
{
	char **cmd1;
	//char **cmd2;
	char **cmd3;
	t_cmd *cmd01;
	//t_cmd *cmd02;
	t_cmd *cmd03;
	int		stdout_save, stdin_save;

	cmd1 = ft_split_char("ls -l", ' ');
	//cmd2 = ft_split_char("grep a", ' ');
	cmd3 = ft_split_char("wc -c", ' ');
	cmd01 = creating_cmd(cmd1, 0, 1);
	//cmd02 = creating_cmd(cmd2, 1, 1);
	cmd03 = creating_cmd(cmd3, 1, 0);
	add_cmd(infos, cmd01);
	//add_cmd(infos, cmd02);
	add_cmd(infos, cmd03);
	check_paths(infos);
	stdout_save = dup(STDOUT_FILENO);
	stdin_save = dup(STDIN_FILENO);
	exec_cmds2(infos, envp);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
}
