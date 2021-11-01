/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_getters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:16 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 17:27:45 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(t_infos *infos, int index)
{
	int		i;
	char	*key;

	i = 0;
	if (!infos->envs || index < 0 || !infos->envs[index])
		return (NULL);
	while (infos->envs[index][i] != '\0' && infos->envs[index][i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (infos->envs[index][i] != '\0' && infos->envs[index][i] != '=')
	{
		key[i] = infos->envs[index][i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(t_infos *info, char *key)
{
	int		index;
	int		i;
	int		counter;
	char	*value;
	size_t	len_value;

	index = find_pos_key(info, key);
	if (index < 0 || !info->envs || !ft_strchr(info->envs[index], '='))
		return (NULL);
	len_value = ft_strlen(info->envs[index]) - (ft_strlen(key) + 1);
	counter = ft_strlen(key) + 1;
	if (len_value == 0)
		return (ft_strdup(""));
	if (len_value > 0)
	{
		value = (char *)malloc(sizeof(char) * (len_value + 1));
		if (!value)
			print_error(E_MALLOC, info);
		i = 0;
		while (info->envs[index][counter] != '\0')
			value[i++] = info->envs[index][counter++];
		value[i] = '\0';
		return (value);
	}
	return (NULL);
}

char	*get_line(t_infos *infos, int index)
{
	char	*line;

	if (!infos->envs || index < 0)
		return (NULL);
	line = ft_strdup(infos->envs[index]);
	if (!line)
		return (NULL);
	return (line);
}

char	**get_env_tab(char **envp)
{
	char	**envs;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	envs = (char **)malloc(sizeof(char *) *(i + 1));
	if (!envs)
		return (NULL);
	i = -1;
	while (envp[++i])
		envs[i] = ft_strdup(envp[i]);
	envs[i] = NULL;
	return (envs);
}

char	*get_exit_code(void)
{
	char	*exit_code;
	int		last_return_code;

	last_return_code = *get_error_code();
	if (last_return_code > 255 || last_return_code < 0)
		exit_code = ft_itoa(255);
	else
		exit_code = ft_itoa(last_return_code);
	if (!exit_code)
		exit_code = ft_strdup("1");
	return (exit_code);
}
