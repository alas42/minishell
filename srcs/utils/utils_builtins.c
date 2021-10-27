/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:06:10 by avogt             #+#    #+#             */
/*   Updated: 2021/10/22 19:30:49 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isalpha(arg[i]) && !(arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

char	*join_args(t_cmd *cmd, t_infos *infos)
{
	char	*final_str;
	int		total_len;
	int		i;

	i = 0;
	total_len = 1;
	while (cmd->arg[++i])
		total_len += ft_strlen(cmd->arg[i]);
	final_str = malloc(sizeof(char) * (total_len + i - 1));
	if (!final_str)
		print_error(E_MALLOC, infos);
	final_str[0] = '\0';
	i = 0;
	while (cmd->arg[++i])
	{
		if (i != 1)
			final_str = ft_strcat(final_str, " ");
		final_str = ft_strcat(final_str, cmd->arg[i]);
	}
	return (final_str);
}
