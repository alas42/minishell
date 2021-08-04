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

enum e_file_end { READ, WRITE };

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

typedef struct s_env
{
	char			*pair;
	int				order;
	struct s_env	*next;
}					t_env;

typedef struct s_infos
{
    int				pipe_a[2];
	int				pipe_b[2];
	int				nb_pipe;
	int				nb_cmd;
	int				index_cmd;
	char			*line;
	char			**paths;
	int				pos_path;
	struct s_cmd	*first_cmd;
	struct s_env	*first_env;
}					t_infos;

int		find_pos_key(t_infos *infos, char *to_find);
int		add_path(char **arg, char *path, int len_path);
int		ft_exists(char *file_path);
void	init_cmds(t_infos *infos, char *str);
void	free_infos(t_infos *infos);
void	check_paths(t_infos *infos);
void	ft_free_tab_ptr(char **ptr);
int		exec_cmds(t_infos *infos, char **envp);
t_cmd	*get_cmd(t_infos *infos);
void	tests_exec_cmds(t_infos *infos, char **envp);

void	add_cmd(t_infos *infos, t_cmd *new);
t_cmd	*creating_cmd(char **arg, int pipe_in, int pipe_out);
int		open_fds(t_infos *infos, t_cmd *cmd);
int		close_fds(t_infos *infos, t_cmd *cmd);

void	test_pwd(void);
char	*mini_pwd(void);

int		mini_cd(char *path);
void	test_cd(void);

void	test_export(t_infos *infos);
char	**get_env(char **envp);
void	get_env_list(t_infos *infos, char **envp);
char	*get_pair(t_infos *infos, int index);

#endif
