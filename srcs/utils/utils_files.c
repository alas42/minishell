/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:30:31 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 15:31:04 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exists(char *file_path)
{
	struct stat	file_info;
	int			ret;

	ret = stat(file_path, &file_info);
	if (ret == 0)
		return (1);
	return (0);
}
