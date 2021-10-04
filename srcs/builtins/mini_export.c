#include "../../includes/minishell.h"

/*
**
** Export without arg - print in ascii order the tab of ptrs with some changes
** 1. It displays the word "export" followed by a whitespace
** 2. It displays the key
** 3. It displays a opening double quote
** 4. It displays all the values of the key
** 5. It displays the closing double quote
** 6. It displays '\n'
**
*/
static int	print_line(t_infos *infos, int index)
{
	char	*key;
	char	*value;
	char	*final_str;

	key = get_key(infos, index);
	value = get_value(infos, key);
	if (!key || !value)
		return (0);
	final_str = (char *)malloc(sizeof(char)
			* (ft_strlen(key) + ft_strlen(value) + 11));
	if (!final_str)
		return (0);
	final_str[0] = '\0';
	final_str = ft_strcat(final_str, "export ");
	final_str = ft_strcat(final_str, key);
	final_str = ft_strcat(final_str, "=");
	final_str = ft_strcat(final_str, "\"");
	final_str = ft_strcat(final_str, value);
	final_str = ft_strcat(final_str, "\"");
	ft_putendl_fd(final_str, STDOUT_FILENO);
	free(key);
	free(value);
	free(final_str);
	return (1);
}

static int	print_asci_order(t_infos *infos, int num, int *order)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < num)
	{
		tmp = 0;
		while (tmp < num)
		{
			if (order[tmp] == i)
			{
				order[tmp] = -1;
				print_line(infos, tmp);
				i = -1;
				break ;
			}
			tmp++;
		}
		i++;
	}
	free(order);
	return (1);
}

void	print_export(t_infos *infos)
{
	int	number_env;
	int	counter[2];
	int	*order;

	counter[0] = 0;
	while (infos->envs[counter[0]])
		counter[0]++;
	number_env = counter[0];
	order = (int *)malloc(sizeof(int) * number_env);
	if (!order)
		print_error(E_MALLOC, infos);
	counter[0] = 0;
	while (counter[0] < number_env)
		order[counter[0]++] = 0;
	counter[0] = -1;
	while (++counter[0] < number_env)
	{
		counter[1] = -1;
		while (++counter[1] < number_env)
			if (counter[0] != counter[1])
				if (ft_strcmp(infos->envs[counter[0]],
						infos->envs[counter[1]]) > 0)
					order[counter[0]] = order[counter[0]] + 1;
	}
	print_asci_order(infos, number_env, order);
}

int	mini_export(t_infos *infos, t_cmd *cmd)
{
	int		ret_find_path;
	char	**key_value_tab;

	if (!cmd->arg[1])
	{
		if (!infos->envs)
			return (1);
		print_export(infos);
		return (1);
	}
	key_value_tab = ft_split_char(cmd->arg[1], '=');
	ret_find_path = find_pos_key(infos, key_value_tab[0]);
	if (ret_find_path > -1)
	{
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = ft_strdup(cmd->arg[1]);
	}
	else
		infos->envs = add_env_tab(infos->envs, cmd->arg[1]);
	ft_free_tab_ptr(key_value_tab);
	return (0);
}
