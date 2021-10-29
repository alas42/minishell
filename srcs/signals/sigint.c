/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:22:52 by avogt             #+#    #+#             */
/*   Updated: 2021/10/29 17:25:38 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_not_global_but_static(int status)
{
	*get_not_global_but_static() = status;
}

int	*get_not_global_but_static(void)
{
	static int	exit_code = 0;

	return (&exit_code);
}

void	sigint_handler(int status)
{
	int	code;

	code = 130;
	set_not_global_but_static(code);
	(void)status;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
