#include "../../includes/minishell.h"

void	sigint_handler(int status)
{
	(void)status;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}
