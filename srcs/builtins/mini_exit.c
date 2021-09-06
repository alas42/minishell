#include "../../includes/minishell.h"

/*
**
** Of course, exit frees and quits the program
** But then again, should it send signals and return a special code ?
**
** MAYBE SOMETHING WITH FD ?
**
*/

int	mini_exit(t_infos *infos, t_cmd *cmd)
{
	(void)cmd;
	free_infos(infos);
	//rl_clear_history();
	exit(0);
}
