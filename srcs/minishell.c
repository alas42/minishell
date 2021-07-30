#include "../includes/minishell.h"

t_infos	init_infos(char **envp)
{
	t_infos	infos;

	infos.pos_path = find_pos_path(envp, "PATH");
	infos.paths = ft_split_char(&envp[infos.pos_path][5], ':');
	infos.nb_cmd = 0;
	infos.first = NULL;
	return (infos);
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
	char	**cmds;
	char	*line;
	t_infos	infos;

	int_mode = isatty(STDIN_FILENO);
	infos = init_infos(envp);
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
		{
			line = readline("$ ");
			cmds = ft_split_char(line, ' ');
			free(line);
			ft_free_tab_ptr(cmds);
		}
	}
}
