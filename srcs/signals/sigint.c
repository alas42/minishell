/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:22:52 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:22:56 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int status)
{
	(void)status;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
