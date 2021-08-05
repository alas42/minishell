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

int	mini_echo(char **arg)
{
	int i;
	int	new_line;

	new_line = 1;
	i = 1;
	is_new_line(arg, &i, &new_line);
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
	char *arg[7];
	//char *arg2[2];

	arg[0] = "echo";
	arg[1] = "-nnnnnnnn";
	arg[2] = "-nnnnnnnnn";
	arg[3] = "-nnnnnnnaaaaa";
	arg[4] = "-nnnnnnnnnnnn";
	arg[5] = "abc";
	arg[6] = NULL;
	/*arg2[0] = "echo";
	arg2[1] = NULL;*/
	mini_echo(arg);
	//mini_echo(arg2);
}
