#include "../../includes/minishell.h"

/*
**
** Of course, exit frees and quits the program
** But then again, should it send signals and return a special code ?
**
** MAYBE SOMETHING WITH FD ?
** 
*/

int	mini_exit(t_infos *infos, t_cmd *cmd __attribute__((unused)))
{
	free_infos(infos);
	free(infos);
	exit(0);
}

/*
void	test_exit(t_infos *infos)
{
	mini_exit(infos);
}
*/
