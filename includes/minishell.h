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

/*
**
** Chained list and tab of pointers to char for the same env
** Why ?
** We have to pass a tab of pointers in execve.
** But we have to print them in two different ways in env and export builtins
**
** Env -> In alphabetical order BUT without double quotes around the value
** Export -> In normal order from envp but the last before NULL will be the terminal
** When adding a key=value, add it just before the line from terminal
**
*/

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
	char			**envs;
}					t_infos;

int		find_pos_key(t_infos *infos, char *to_find);
int		add_path(char **arg, char *path, int len_path);
int		ft_exists(char *file_path);

void	init_cmds(t_infos *infos, char *str);
void	free_infos(t_infos *infos);
void	free_cmd_list(t_infos *infos);

void	check_paths(t_infos *infos);
void	ft_free_tab_ptr(char **ptr);
int		exec_cmds(t_infos *infos, char **envp);
t_cmd	*get_cmd(t_infos *infos);
void	tests_exec_cmds(t_infos *infos, char **envp);

void	add_cmd(t_infos *infos, t_cmd *new);
t_cmd	*creating_cmd(char **arg, int pipe_in, int pipe_out);

int		child_fds(t_infos *infos, t_cmd *cmd);
int		parent_fds(t_infos *infos, t_cmd *cmd);

void	test_pwd(void);
char	*mini_pwd(void);

int		mini_cd(t_infos *infos, char *path);
void	test_cd(t_infos *infos);

int		mini_export(t_infos *infos, char *key, char *value);
void	test_export(t_infos *infos);

void	add_env(t_infos *infos, t_env *new);
t_env	*creating_env(char *str);
void	get_env_list(t_infos *infos, char **envp);
char	*get_pair(t_infos *infos, int index);
void	free_env_list(t_infos *infos);

int		mini_env(t_infos *infos);
void	test_env(t_infos *infos);

char	**get_env_tab(char **envp);
void	print_env_tab(t_infos *infos);
char	**add_env_tab(char **envs, char *key_value_str);
char	**remove_env_tab(t_infos *infos, char *key);
int		change_line_env_tab(t_infos *infos, char *key,  char *value);
char	*create_pair_key_value(char *key, char *value);

int		mini_unset(t_infos *infos, char *key);
void	test_unset(t_infos *infos);

int		mini_echo(char **arg);
void	test_echo(void);

/*
**
**	Tests function not recursive
**
*/
void	tests_exec_cmds2(t_infos *infos, char **envp);
int		exec_cmds2(t_infos *infos, char **envp);
#endif
