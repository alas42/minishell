#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include "libft.h"

void	ft_free_tab_ptr(char **ptr);


int		add_path(char **arg, char *path, int len_path);
/*
** find_pos_path - search the envp variable 
** returns the index of path variable 
**/
int		find_pos_path(char **envp, char *to_find);
int		ft_exists(char *file_path);
void	check_paths(char **paths, char **arg);
#endif
