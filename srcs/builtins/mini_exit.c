/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:19:42 by avogt             #+#    #+#             */
/*   Updated: 2021/10/05 13:19:43 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_exit(t_infos *infos, t_cmd *cmd)
{
	(void)cmd;
	free_infos(infos);
	rl_clear_history();
	exit(0);
}
