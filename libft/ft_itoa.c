/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:57:56 by avogt             #+#    #+#             */
/*   Updated: 2021/10/01 12:04:33 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_get_len(int n)
{
	int	len;
	int	tmp;

	tmp = n;
	len = 1;
	if (n < 0)
		len = 2;
	tmp = n;
	while (tmp / 10 != 0)
	{
		tmp = tmp / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;

	len = ft_get_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	if (n == -2147483648)
	{
		result[1] = '2';
		n = 147483648;
	}
	if (n < 0)
		n = n * -1;
	result[len] = '\0';
	while (len--)
	{
		result[len] = ((n % 10) + '0');
		n /= 10;
		if (n == 0)
			return (result);
	}
	return (result);
}
