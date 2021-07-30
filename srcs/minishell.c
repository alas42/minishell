#include "../includes/minishell.h"

//don't know what structure we will be using but there's a start I guess
int	main(int argc, char **argv, char **envp)
{
	int		int_mode;
	char	**cmds;
	char	*line;

	int_mode = isatty(STDIN_FILENO);
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
		{
			line = readline("~$ ");
			cmds = ft_split_char(line, ' ');
			free(line);
		}
		ft_free_tab_ptr(cmds);
	}
}