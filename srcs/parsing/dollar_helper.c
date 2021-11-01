/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:56:45 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 10:59:08 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dollar_numdigit(char *content, char *str, t_infos *info)
{
	char	*value;

	value = get_dollar_value(info, str);
	value = check_dollar_ret_val(value);
	content = merge_content(content, value, 0);
	free(value);
	return (content);
}

int	check_if_literal(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (1);
	if (!(ft_isalpha(str[0])) && !(ft_isdigit(str[0])) && str[0] != '?')
		return (1);
	return (0);
}

char	*get_dollar_literal(char *str, char *content, t_infos *info)
{
	char	*temp;
	int		len;

	len = ft_strlen(str);
	if (len == 0)
		temp = char_to_str('$', info);
	else if (!(ft_isalpha(str[0])) && !(ft_isdigit(str[0])) && str[0] != '?')
	{
		temp = char_to_str('$', info);
		temp = merge_content(temp, str, 0);
	}
	content = merge_content(content, temp, 0);
	free(temp);
	return (content);
}
