#include "../../includes/minishell.h"

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
**
*/

int	mini_unset(t_infos *infos, t_cmd *cmd)
{
	infos->envs = remove_env_tab(infos, cmd->arg[1]);
	return (1);
}

/*
void	test_unset(t_infos *infos)
{
	mini_unset(infos, "test_key");
	mini_unset(infos, "testare_key");
	print_env_tab(infos);
}
*/
