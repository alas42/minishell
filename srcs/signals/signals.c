/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:24:30 by avogt             #+#    #+#             */
/*   Updated: 2021/10/29 14:54:59 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ignore_signals(void)
{
	signal(SIGTRAP, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
}

void	ignore_all_signals(void)
{
	ignore_signals();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	ignore_signals();
}
