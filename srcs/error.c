#include "../includes/minishell.h"

void	print_error(int state, t_infos *infos)
{
	if (state == E_MALLOC)
		ft_putendl_fd("Allocation error", STDERR_FILENO);
	else if (state == E_OPEN)
		ft_putendl_fd("Open error", STDERR_FILENO);
	else if (state == E_CLOSE)
		ft_putendl_fd("Close error", STDERR_FILENO);
	else if (state == E_FORK)
		ft_putendl_fd("Fork error", STDERR_FILENO);
	else if (state == E_PIPE)
		ft_putendl_fd("Pipe error", STDERR_FILENO);
	else if (state == E_DUP)
		ft_putendl_fd("Dup error", STDERR_FILENO);
	else if (state == E_DUP2)
		ft_putendl_fd("Dup2 error", STDERR_FILENO);
	else if (state == E_EXECVE)
		ft_putendl_fd("Execve error", STDERR_FILENO);
	free_infos(infos);
	//rl_clear_history();
	exit(0);
}
