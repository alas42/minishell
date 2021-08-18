#include "../../includes/minishell.h"

/*
**
** Echo like the others shall have a **arg filled
** But It doesn't have to be NULL like many other
** Only Echo and Export treats their arguments
**
*/

void	is_new_line(char **arg, int *i, int *new_line)
{
	int	j;

	while (arg[*i])
	{
		j = 0;
		if (arg[*i][j] == '-')
			j++;
		else
			return ;
		while (arg[*i][j])
		{
			if (arg[*i][j] == 'n')
				*new_line = 0;
			else
			{
				if (*i == 1)
					*new_line = 1;
				return ;
			}
			j++;
		}
		*i = *i + 1;
	}
}

int	mini_echo(t_infos *infos, t_cmd *cmd)
{
	int	i;
	int	new_line;

	(void)infos;
	new_line = 1;
	i = 1;
	is_new_line(cmd->arg, &i, &new_line);
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
		i++;
		if (cmd->arg[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
/*
void	test_echo(void)
{
	char	*arg[7];

	arg[0] = "echo";
	arg[1] = "-nnnnnnnn";
	arg[2] = "-nnnnnnnnn";
	arg[3] = "-nnnnnnnaaaaa";
	arg[4] = "-nnnnnnnnnnnn";
	arg[5] = "abc";
	arg[6] = NULL;
	mini_echo(arg);
}*/
