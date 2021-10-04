#include "../../includes/minishell.h"

int	mini_exit(t_infos *infos, t_cmd *cmd)
{
	(void)cmd;
	free_infos(infos);
	rl_clear_history();
	exit(0);
}
