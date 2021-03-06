/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:28:51 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 12:51:53 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_double_char(char **args)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strdup("");
	while (args[++i])
		temp = merge_content(temp, args[i], 1);
	temp = remove_last_space(temp);
	return (temp);
}

char	*get_word(char *word, int size, int start, int end)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (end < 0)
		end = ft_strlen(word);
	i = 0;
	while (start < end)
	{
		str[i] = word[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*check_special_char(t_infos *info, char *content, char *word)
{
	char	*dollar;
	char	*rest;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (word[i])
	{
		if (!(ft_isalpha(word[i])) && !(ft_isdigit(word[i])))
			break ;
		i++;
	}
	j = (ft_strlen(word) - i) + 1;
	dollar = get_word(word, i + 1, 0, i);
	rest = get_word(word, j, i, -1);
	value = get_dollar_value(info, dollar);
	value = check_dollar_ret_val(value);
	value = merge_content(value, rest, 0);
	free(rest);
	content = merge_content(content, value, 0);
	free(value);
	free(dollar);
	return (content);
}

char	*handle_question(t_infos *info, char *content, char *word)
{
	char	*dollar;
	char	*rest;
	char	*value;
	int		j;

	dollar = (char *)malloc(sizeof(char) * 2);
	if (dollar == NULL)
		print_error(E_MALLOC, info);
	dollar[0] = word[0];
	dollar[1] = '\0';
	j = ft_strlen(word);
	rest = get_word(word, j, 1, -1);
	if (dollar[0] == '?')
		value = get_exit_code();
	else
	{
		value = get_dollar_value(info, dollar);
		value = check_dollar_ret_val(value);
	}
	value = merge_content(value, rest, 0);
	free(rest);
	content = merge_content(content, value, 0);
	free(value);
	free(dollar);
	return (content);
}

char	*check_dollar_ret_val(char *value)
{
	char	**temp;
	int		i;
	int		len;

	i = -1;
	temp = ft_split(value, ' ');
	free(value);
	value = ft_strdup("");
	while (temp[++i])
	{
		if (ft_isallspace(temp[i]))
			value = merge_content(value, temp[i], 1);
	}
	len = ft_strlen(value);
	if (len > 0)
		value[len - 1] = '\0';
	if (len == 0)
		value[len] = '\0';
	free_doub_char(temp);
	return (value);
}
