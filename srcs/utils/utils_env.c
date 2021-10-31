/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:23 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 15:20:00 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_pair_key_value(char *key, char *value)
{
	char	*key_value_str;
	size_t	length;

	length = ft_strlen(key) + ft_strlen(value) + 4;
	key_value_str = (char *)malloc(sizeof(char) * (length));
	if (!key_value_str)
		return (NULL);
	key_value_str[0] = '\0';
	key_value_str = ft_strcat(key_value_str, key);
	key_value_str = ft_strcat(key_value_str, "=");
	key_value_str = ft_strcat(key_value_str, value);
	key_value_str = ft_strcat(key_value_str, "\0");
	return (key_value_str);
}

int	change_line_env_tab(t_infos *infos, char *key, char *value)
{
	char	*key_value_str;
	int		ret_find_path;

	key_value_str = NULL;
	ret_find_path = find_pos_key(infos, key);
	if (ret_find_path > -1)
	{
		key_value_str = create_pair_key_value(key, value);
		if (!key_value_str)
			print_error(E_MALLOC, infos);
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = ft_strdup(key_value_str);
		free(key_value_str);
		return (1);
	}
	else
	{
		key_value_str = create_pair_key_value(key, value);
		if (!key_value_str)
			print_error(E_MALLOC, infos);
		infos->envs = add_env_tab(infos->envs, key_value_str);
		return (1);
	}
	return (0);
}

char	**add_env_tab(char **envs, char *key_value_str)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	if (envs)
		while (envs[i])
			i++;
	new_tab = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	j = -1;
	while (++j < i - 1)
		new_tab[j] = ft_strdup(envs[j]);
	new_tab[j++] = ft_strdup(key_value_str);
	if (i != 0)
		new_tab[j++] = ft_strdup(envs[i - 1]);
	new_tab[j] = NULL;
	ft_free_tab_ptr(envs);
	return (new_tab);
}

void	print_env_tab(t_infos *infos)
{
	int	i;

	i = 0;
	if (!infos->envs)
		return ;
	while (infos->envs[i])
	{
		ft_putendl_fd(infos->envs[i], STDOUT_FILENO);
		i++;
	}
}

int	add_layer_shlvl(t_infos *infos)
{
	char	*value_shlvl;
	int		pos_shlvl;
	int		shlvl_int;

	value_shlvl = NULL;
	pos_shlvl = find_pos_key(infos, "SHLVL");
	if (pos_shlvl > -1)
	{
		value_shlvl = get_value(infos, "SHLVL");
		if (value_shlvl == NULL)
			return (0);
		shlvl_int = ft_atoi(value_shlvl) + 1;
		free(value_shlvl);
		value_shlvl = ft_itoa(shlvl_int);
		if (!value_shlvl)
			return (0);
		pos_shlvl = change_line_env_tab(infos, "SHLVL", value_shlvl);
		free(value_shlvl);
		return (pos_shlvl);
	}
	return (0);
}
