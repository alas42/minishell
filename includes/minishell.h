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

typedef struct s_cmd
{
    char    		**arg;
    int     		pipe[2];
    int     		process;
    int     		fd_outfile;
    int     		fd_infile;
	struct s_cmd	*next;
}           		t_cmd;

/*
**
** Either a chained list or an allocated tab
**
*/
typedef struct s_infos
{
	int				nb_cmd;
	char			**paths;
	int				pos_path;
	struct s_cmd	*first;
}					t_infos;

/*
** find_pos_path - search the envp variable 
** returns the index of path variable 
**/
int		find_pos_path(char **envp, char *to_find);
int		add_path(char **arg, char *path, int len_path);
int		ft_exists(char *file_path);
void	check_paths(char **paths, char **arg);

void	ft_free_tab_ptr(char **ptr);
#endif
