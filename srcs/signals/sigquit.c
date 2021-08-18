#include "../../includes/minishell.h"

void	sigquit_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\b\b  \b\b", 6);
}
