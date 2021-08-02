#include "../includes/minishell.h"

t_infos	*init_infos(char **envp)
{
	t_infos	*infos;

	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->pos_path = find_pos_path(envp, "PATH");
	infos->paths = ft_split_char(&envp[infos->pos_path][5], ':');
	infos->nb_cmd = 0;
	infos->first = NULL;
	return (infos);
}

//add error checking at return
void	init_cmds(t_infos *infos, char *str)
{
	t_cmd *cmd;
	t_cmd *tmp;

	tmp = infos->first;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->arg = ft_split_char(str, ' ');
	if (tmp == NULL)
		cmd->prec = NULL;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		cmd->prec = tmp;
	}
	cmd->next = NULL;
	infos->first = cmd;
}

/*
**
** They speak about one global for exit or error status
** don't know what structure we will be using but there's a start I guess
** 
** Step 1:
** An elaborate pipex that can execute only one func if there is no pipe but more than two if needed
** 
** Step 1.1:
** Parsing without execptions to fill structs with correct infos
**
** Step 1.2:
** Recursive or looping method that executes cmds with correct pipes
**
** Step 1.3:
** Add exceptions to parsing - check for builtins
**
** Step 1.4:
** 
**
*/
int	main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **envp __attribute__((unused)))
{
	int		int_mode;
	t_infos	*infos;

	int_mode = isatty(STDIN_FILENO);
	infos = init_infos(envp);
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
		{
			infos->line = readline("$ ");
			//parsing into tokens before adding to history
			if (infos->line)
				add_history(infos->line);
			//it wont be like this of course, it takes only one command for now
			init_cmds(infos, infos->line);
			check_paths(infos);
			free_infos(infos);
		}
	}
	ft_free_tab_ptr(infos->paths);
	free(infos);
}
