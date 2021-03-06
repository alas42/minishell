/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:31 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 17:31:04 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	mini_export_end(t_infos *infos, char **key_value, char *str)
{
	int	ret_find_path;

	ret_find_path = find_pos_key(infos, key_value[0]);
	if (ret_find_path > -1)
	{
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = ft_strdup(str);
	}
	else
		infos->envs = add_env_tab(infos->envs, str);
	ft_free_tab_ptr(key_value);
	free(str);
}

int	mini_export(t_infos *infos, t_cmd *cmd)
{
	char	**key_value_tab;
	char	*str_to_add;

	if (!cmd->arg[1])
	{
		if (!infos->envs)
			return (1);
		print_export(infos);
		return (0);
	}
	key_value_tab = ft_split_char(cmd->arg[1], '=');
	str_to_add = join_args(cmd, infos);
	if (!check_tab_identifier(key_value_tab, str_to_add))
	{
		mini_export_end(infos, key_value_tab, str_to_add);
		return (0);
	}
	return (1);
}
