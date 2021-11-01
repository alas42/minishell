/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:16:20 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 17:30:44 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*continue_concatenation(char *final_str, char *value)
{
	final_str = ft_strcat(final_str, "=");
	final_str = ft_strcat(final_str, "\"");
	final_str = ft_strcat(final_str, value);
	final_str = ft_strcat(final_str, "\"");
	return (final_str);
}

int	print_line(t_infos *infos, int index)
{
	char	*key;
	char	*value;
	char	*final_str;

	key = get_key(infos, index);
	value = get_value(infos, key);
	if (!key)
		return (0);
	final_str = (char *)malloc(sizeof(char)
			* (ft_strlen(key) + ft_strlen(value) + 11));
	if (!final_str)
		print_error(E_MALLOC, infos);
	final_str[0] = '\0';
	final_str = ft_strcat(final_str, "export ");
	final_str = ft_strcat(final_str, key);
	if (value)
	{
		final_str = continue_concatenation(final_str, value);
		free(value);
	}
	ft_putendl_fd(final_str, STDOUT_FILENO);
	free(key);
	free(final_str);
	return (1);
}
