/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:37:09 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 11:47:03 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_infos(t_infos *infos)
{
	infos->parse_error = 0;
	free(infos->line);
	free_tokens(infos);
	free_cmnds(infos);
}

void	reinit_infos(t_infos *infos)
{
	infos->index_cmd = 0;
	infos->nb_cmd = 0;
	infos->nb_pipe = 0;
	infos->first_cmd = NULL;
	infos->commands = NULL;
	start_parsing(infos);
	signal(SIGINT, sigint_handler);
}

t_infos	*init_infos(char **envp)
{
	t_infos	*infos;
	char	*line_envp;

	line_envp = NULL;
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->first_env = NULL;
	infos->envs = get_env_tab(envp);
	infos->pos_path = find_pos_key(infos, "PATH");
	line_envp = get_line(infos, infos->pos_path);
	infos->paths = ft_split_char(line_envp, ':');
	add_layer_shlvl(infos);
	infos->parse_error = 0;
	infos->nb_cmd = 0;
	infos->tokens = NULL;
	set_error_code(0);
	infos->nb_pipe = 0;
	infos->index_cmd = 0;
	infos->first_cmd = NULL;
	infos->commands = NULL;
	free(line_envp);
	return (infos);
}
