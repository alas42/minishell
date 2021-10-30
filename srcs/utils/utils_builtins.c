/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:06:10 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 13:28:37 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isalphadigit(int c)
{
	int	char_c;

	char_c = c;
	if (char_c > 47 && char_c < 58)
		return (1);
	if (char_c > 64 && char_c < 91)
		return (1);
	else if (char_c > 96 && char_c < 123)
		return (1);
	return (0);
}

int	check_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (i == 0)
		{
			if (!ft_isalpha(arg[i]) && !(arg[i] == '_'))
				return (1);
		}
		else
		{
			if (!ft_isalphadigit(arg[i]) && !(arg[i] == '_'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_tab_identifier(char **key_value_tab, char *str)
{
	int	ret;

	ret = 0;
	if (!key_value_tab)
		ret = 1;
	else if (!ft_strncmp(str, "=", 1))
		ret = 1;
	else if (check_valid_identifier(key_value_tab[0]))
		ret = 1;
	if (ret == 1)
	{
		ft_putstr_fd("minishell: export: « ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(" » : identifiant non valable", STDERR_FILENO);
		ft_free_tab_ptr(key_value_tab);
		free(str);
	}
	return (ret);
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
