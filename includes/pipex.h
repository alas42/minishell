/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:51:35 by avogt             #+#    #+#             */
/*   Updated: 2021/07/30 16:51:55 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_helper
{
	char	**paths;
	char	**arg;
	char	**arg2;
	int		pipe[2];
	int		process[2];
	int		pos_path;
	int		fd_outfile;
	int		fd_infile;
}				t_helper;

void		ft_write_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_len(char *s);
void		ft_usage(void);
void		ft_free_tab_ptr(char **ptr);
void		ft_free_struct_helper(t_helper *helper);
int			ft_exists(char *s);
int			add_path(char **arg, char *path, int len_path);
int			find_pos_path(char **envp, char *to_find);
void		check_paths(t_helper *helper);
char		**ft_parsed_cmd(char *str, char split_char);
t_helper	*init_helper(char *av[], char **envp);
void		process_one(t_helper *helper, char **envp);
void		not_found(char *path, int nb_process, int nb, t_helper *helper);
void		ft_error_functions(int nb, t_helper *helper);
void		ft_error_sysfunctions(int nb, t_helper *helper);

#endif