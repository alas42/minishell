#include "../../includes/minishell.h"

int	mini_env(t_infos *infos, t_cmd *cmd)
{
	(void)cmd;
	print_env_tab(infos);
	return (0);
}
