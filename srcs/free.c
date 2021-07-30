/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:14:52 by avogt             #+#    #+#             */
/*   Updated: 2021/07/05 11:15:13 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_tab_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	ft_free_struct_helper(t_helper *helper)
{
	ft_free_tab_ptr(helper->paths);
	ft_free_tab_ptr(helper->arg);
	ft_free_tab_ptr(helper->arg2);
	free(helper);
	helper = NULL;
}
