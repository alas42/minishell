/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:20:13 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 19:06:50 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**copy_new_tab(t_infos *infos, int pos_key, char **new_tab)
{
	int	i;

	i = -1;
	while (infos->envs[++i])
	{
		if (i < pos_key)
		{
			new_tab[i] = ft_strdup(infos->envs[i]);
			if (!new_tab[i])
			{
				ft_free_tab_ptr(new_tab);
				return (NULL);
			}
		}
		else if (i > pos_key)
		{
			new_tab[i - 1] = ft_strdup(infos->envs[i]);
			if (!new_tab[i - 1])
			{
				ft_free_tab_ptr(new_tab);
				return (NULL);
			}
		}
	}
	return (new_tab);
}

int	remove_env_tab(t_infos *infos, char *key)
{
	int		i;
	char	**new_tab;
	int		pos_key;

	i = 0;
	while (infos->envs[i])
		i++;
	new_tab = (char **)malloc(sizeof(char *) * i);
	if (!new_tab)
		return (2);
	pos_key = find_pos_key(infos, key);
	if (pos_key == -1)
	{
		free(new_tab);
		return (0);
	}
	new_tab = copy_new_tab(infos, pos_key, new_tab);
	if (!new_tab)
		return (2);
	new_tab[i - 1] = NULL;
	ft_free_tab_ptr(infos->envs);
	infos->envs = new_tab;
	return (0);
}

static int	print_error_unset(char *str)
{
	ft_putstr_fd("minishell: unset: « ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" » : identifiant non valable", STDERR_FILENO);
	return (1);
}

int	mini_unset(t_infos *infos, t_cmd *cmd)
{
	int	i;
	int	ret;
	int	final_ret;

	i = 1;
	ret = 0;
	final_ret = 0;
	if (infos->envs)
	{
		while (cmd->arg[i])
		{
			if (check_valid_identifier(cmd->arg[i]))
				final_ret = print_error_unset(cmd->arg[i]);
			ret = remove_env_tab(infos, cmd->arg[i]);
			if (ret == 2)
				print_error(E_MALLOC, infos);
			i++;
		}
	}
	return (final_ret);
}
