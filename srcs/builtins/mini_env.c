#include "../../includes/minishell.h"

int	mini_env(t_infos *infos)
{
	print_env_tab(infos);
	return (1);
}

void	test_env(t_infos *infos)
{
	mini_env(infos);
}
