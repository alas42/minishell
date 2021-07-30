/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:12:40 by avogt             #+#    #+#             */
/*   Updated: 2021/07/30 14:39:04 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_lenl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static void		ft_init_next(char **next, char *buff)
{
	char	*t;

	t = NULL;
	if (*next != NULL)
	{
		t = ft_strdup(*next);
		ft_strdel(next);
	}
	else
		t = ft_strdup("");
	*next = ft_strjoin(t, buff);
	free(t);
}

static int		ft_read(int fd, char **next)
{
	int		ret;
	char	tmp[BUFF_SIZE + 1];

	ret = 0;
	if (*next != NULL && ft_strchr(*next, '\n') != NULL)
		return (1);
	ret = read(fd, tmp, BUFF_SIZE);
	while (ret > 0)
	{
		tmp[ret] = '\0';
		ft_init_next(next, tmp);
		if (ft_strchr(*next, '\n') != NULL)
			return (1);
		ret = read(fd, tmp, BUFF_SIZE);
	}
	if (ret == -1)
		return (-1);
	return (1);
}

static void		reduce_next(char **next)
{
	char	*tmp;

	tmp = ft_strsub(*next, ft_lenl(*next) + 1, ft_strlen(*next)
			- (ft_lenl(*next) + 1));
	ft_strdel(next);
	*next = ft_strdup(tmp);
	ft_strdel(&tmp);
}

int				get_next_line(int fd, char **line)
{
	static char	*next = NULL;

	if (fd < 0 || line == NULL || ft_read(fd, &next) == -1)
		return (-1);
	if (next)
	{
		if (ft_strchr(next, '\n') != NULL)
		{
			*line = ft_strsub(next, 0, ft_lenl(next));
			reduce_next(&next);
		}
		else
		{
			*line = ft_strdup(next);
			ft_strdel(&next);
			if (ft_strlen(*line) == 0)
			{
				if (*line)
					free(*line);
				return (0);
			}
		}
		return (1);
	}
	return (0);
}
