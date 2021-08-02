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
    int     		process;
    int     		fd_outfile;
    int     		fd_infile;
	int				builtin; //bool
	int				pipe_in; //bool
	int				pipe_out; //bool
	char			*name_infile;
	char			*name_outfile;
	struct s_cmd	*next;
	struct s_cmd	*prec;
}           		t_cmd;

/*
**
** Either a chained list or an allocated tab
**
*/
typedef struct s_infos
{
    int     		pipe[2];
	int				nb_cmd;
	char			*line;
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
void	init_cmds(t_infos *infos, char *str);
void	free_infos(t_infos *infos);
void	check_paths(t_infos *infos);
void	ft_free_tab_ptr(char **ptr);
int		exec_cmds(t_infos *infos, char **envp);
t_cmd	*get_cmd(t_infos *infos);
void	tests_exec_cmds(t_infos *infos, char **envp);
#endif
