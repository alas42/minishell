/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:56:09 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:57:18 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	get_number_words(char *str, char split_char)
{
	int		i;
	int		k;
	int		nb_words;

	i = 0;
	k = 0;
	nb_words = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] != '\0' && str[i] == split_char)
			i++;
		while (str[i] != '\0' && str[i] != split_char)
		{
			if (k == 0)
				nb_words++;
			k++;
			i++;
		}
	}
	return (nb_words);
}

static int	get_number_char(char *str, int *k, char split_char)
{
	int	nb_char;

	nb_char = 0;
	while (str[*k] != '\0' && str[*k] == split_char)
		*k = *k + 1;
	while (str[*k] != '\0' && str[*k] != split_char)
	{
		*k = *k + 1;
		nb_char++;
	}
	return (nb_char);
}

static void	fill_with_char(char *str, char *to_fill, int n, char split_char)
{
	int		i;
	int		k;
	int		nb_words;

	i = 0;
	k = 0;
	nb_words = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == split_char)
			i++;
		while (str[i] != '\0' && str[i] != split_char)
		{
			if (nb_words == n)
				to_fill[k] = str[i];
			k++;
			i++;
		}
		if (nb_words == n)
			to_fill[k] = '\0';
		nb_words++;
		k = 0;
	}
}

char	**ft_split_char(char *str, char split_char)
{
	int		nb[4];
	char	**arg;

	nb[2] = -1;
	nb[3] = 0;
	nb[1] = 0;
	if (!str)
		return (NULL);
	nb[0] = get_number_words(str, split_char);
	arg = (char **)malloc(sizeof(char *) * (nb[0] + 1));
	if (!arg)
		return (NULL);
	arg[nb[0]] = NULL;
	while (++nb[2] < nb[0])
	{
		nb[1] = get_number_char(str, &nb[3], split_char);
		arg[nb[2]] = (char *)malloc(sizeof(char) * (nb[1] + 1));
		if (!arg[nb[2]])
			while (--nb[2] >= 0)
				free(arg[nb[2]]);
		if (!arg[0])
			return (NULL);
		fill_with_char(str, arg[nb[2]], nb[2], split_char);
	}
	return (arg);
}
