#include "../../includes/minishell.h"

/*
**
** Echo like the others shall have a **arg filled
** But It doesn't have to be NULL like many other
** Only Echo and Export treats their arguments
**
**
** I don't know how it will be parsed
** For, now arg[0] will contain echo and arg[1 to n] will contains args or the option -n
**
*/

int	mini_echo(char **arg)
{
	int i;
	int j;
	int	new_line;

	new_line = 1;
	i = 0;
	j = 0;
	if (arg[1] && arg[1][j] == '-')
	{
		i = 2;
		j++;
		while (arg[1][j])
		{
			if (arg[1][j] == 'n')
				new_line = 0;
			else
			{
				new_line = 1;
				i--;
				break ;
			}
			j++;
		}
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		i++;
		if (arg[i])
			ft_putchar_fd(' ', STDOUT_FILENO);

	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}

void	test_echo(void)
{
	char *arg[5];

	arg[0] = "echo";
	arg[1] = "-n";
	arg[2] = "-nnnnnnnnn";
	arg[3] = "-aaaaa";
	arg[4] = NULL;
	mini_echo(arg);
}