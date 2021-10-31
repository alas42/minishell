/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:22:49 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:23:22 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_chars_bash_error(char *s, char *s1, char *s2, char *s3)
{
	free(s);
	free(s1);
	free(s2);
	free(s3);
}

void	close_child_fd_error(t_cmd *cmd)
{
	if (cmd->fd_infile > -1)
		close(cmd->fd_infile);
	if (cmd->fd_outfile > -1)
		close(cmd->fd_outfile);
}
