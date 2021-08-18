#include "../../includes/minishell.h"

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
**
** QUESTION :
** What happens if we type in 'env arg1 arg2 arg3' ?
**
*/

int	mini_env(t_infos *infos, t_cmd *cmd)
{
	(void)cmd;
	print_env_tab(infos);
	return (1);
}

/*
void	test_env(t_infos *infos)
{
	mini_env(infos);
}
*/
