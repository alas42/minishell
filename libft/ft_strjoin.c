/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:03:09 by avogt             #+#    #+#             */
/*   Updated: 2021/07/30 14:33:58 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*fresh;
	unsigned int	tt_len;
	unsigned int	i;

	i = 0;
	tt_len = 1;
	if (s1 != NULL)
		tt_len = ft_strlen(s1) + 1;
	if (s2 != NULL)
		tt_len = tt_len + ft_strlen(s2);
	fresh = (char *)malloc(sizeof(char) * tt_len);
	if (!(fresh))
		return (NULL);
	while (i < tt_len - 1)
	{
		if (s1 != NULL)
			while (*s1 != '\0')
				fresh[i++] = *(s1++);
		if (s2 != NULL)
			while (*s2 != '\0')
				fresh[i++] = *(s2++);
	}
	fresh[i] = '\0';
	return (fresh);
}
