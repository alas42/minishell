#include "../includes/minishell.h"

void	here_doc_ctrl_c(int status)
{
	int	code;

	code = 130;
	set_error_code(code);
	set_interruption(1);
	(void)status;
}

int	*get_interruption(void)
{
	static int	status = 0;

	return (&status);
}

void	set_interruption(int status)
{
	*get_interruption() = status;
}

int	check_for_ctrl_c(void)
{
	if (*get_interruption() == 1 && rl_done == 0)
		rl_done = 1;
	else
		rl_done = 0;
	return (0);
}
