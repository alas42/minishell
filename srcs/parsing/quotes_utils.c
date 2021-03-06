/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:29:53 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:29:54 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*update_quotes_content(t_token *temp, t_infos *info)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(temp->content);
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
	{
		print_error(E_MALLOC, info);
		return (NULL);
	}
	while (i < len - 2)
	{
		str[i] = temp->content[i + 1];
		i++;
	}
	str[i] = '\0';
	free(temp->content);
	return (str);
}

int	check_dollar(char *content)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(content);
	while (i < len)
	{
		if (content[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	update_token_type(t_infos *info, char *from, char *to)
{
	t_token	*temp;
	int		i;

	i = -1;
	temp = info->tokens;
	while (temp)
	{
		if (!(ft_strcmp(temp->type, from)))
		{
			if (!(ft_strcmp(temp->type, "double_quote")))
				i = check_dollar(temp->content);
			free(temp->type);
			if (i != 1)
				temp->type = ft_strdup(to);
			else
				temp->type = ft_strdup("literal_dollar");
			temp->content = update_quotes_content(temp, info);
			break ;
		}
		temp = temp->next;
	}
}
