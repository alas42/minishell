/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:56:31 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:57:18 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s1);
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!(cpy))
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		cpy[len] = s1[len];
		len++;
	}
	cpy[len] = '\0';
	return (cpy);
}
