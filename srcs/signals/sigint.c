/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:22:52 by avogt             #+#    #+#             */
/*   Updated: 2021/11/01 16:32:55 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_error_code(int status)
{
	*get_error_code() = status;
}

int	*get_error_code(void)
{
	static int	exit_code = 0;

	return (&exit_code);
}

void	sigint_handler(int status)
{
	int	code;

	code = 130;
	set_error_code(code);
	(void)status;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
