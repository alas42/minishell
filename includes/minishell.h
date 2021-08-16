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
# include <signal.h>
# include <term.h>
# include "libft.h"

int	g_return_code;

enum e_file_end
{
	READ,
	WRITE
};

enum e_builtin
{
	B_EXIT,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_ENV,
	B_CD,
	B_UNSET
};

enum e_error
{
	E_MALLOC,
	E_FORK,
	E_PIPE,
	E_DUP,
	E_DUP2,
	E_EXECVE,
	E_CLOSE,
	E_OPEN
};

typedef struct s_cmd
{
	char			**arg;
	int				process;
	int				fd_outfile;
	int				fd_infile;
	int				here_doc_in;
	int				builtin;
	int				pipe_in;
	int				pipe_out;
	char			*name_infile;
	char			*name_outfile;
	struct s_cmd	*next;
	struct s_cmd	*prec;
}					t_cmd;

typedef struct s_token
{
	int				pos;
	char			*content;
	char			*type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

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
	struct s_token	*tokens;
	struct s_cmd	*first_cmd;
	struct s_env	*first_env;
	char			**envs;
}					t_infos;

//free.c
void		free_infos(t_infos *infos);
void		free_tokens(t_infos *info);
void		free_cmd_list(t_infos *infos);
void		ft_free_tab_ptr(char **ptr);
void		free_env_list(t_infos *infos);

//parsing.c
void		start_parsing(t_infos *info);

//lexer.c
void		merge_same(t_infos *info);
void		merge_tokens(t_infos *info, int start, int total);
t_token		*join_tokens(t_token *tokens);
void		update_tokens_pos(t_infos *info);

//parsing_init.c
void		get_token_type(t_token *new, t_infos *info, int i);
t_token		*token_init(void);
void		lst_add_back(t_infos *info, t_token *new);
t_token		*ft_lstlast(t_token *lst);
void		add_to_struct(t_infos *info);

//parsing_utils.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isspace_isdigit(char c, char d);
char		*char_to_str(char c);

//print_temp.c Temp Function to be removed later
void		print_info(t_infos *info);
void		print_token_list(t_token *token);

//utils for t_cmds
void		add_cmd(t_infos *infos, t_cmd *new);
t_cmd		*creating_cmd(char **arg, int pipe_in, int pipe_out);
void		init_cmds(t_infos *infos, char *str);
void		tests_exec_cmds(t_infos *infos, char **envp);
t_cmd		*get_cmd(t_infos *infos);

//[----------------exec_cmds.c----------------]
int			child_fds(t_infos *infos, t_cmd *cmd);
int			parent_fds(t_infos *infos, t_cmd *cmd);
int			exec_cmds(t_infos *infos, char **envp);
//[----------------end of exec_cmds.c----------------]

//utils for environment variables (tab)
char		**get_env_tab(char **envp);
void		print_env_tab(t_infos *infos);
char		**add_env_tab(char **envs, char *key_value_str);
int			change_line_env_tab(t_infos *infos, char *key, char *value);
char		**remove_env_tab(t_infos *infos, char *key);
char		*create_pair_key_value(char *key, char *value);
char		*get_value(t_infos *infos, char *key);
char		*get_key(t_infos *infos, int index);
char		*get_line(t_infos *infos, int index);

//[----------------paths.c----------------]
/*
** Returns the index from the environment variable to_find in the tab
*/
int			find_pos_key(t_infos *infos, char *to_find);
int			add_path(char **arg, char *path, int len_path);

/*
** Checks if the paths given corresponds to an existing file
*/
int			ft_exists(char *file_path);
void		check_paths(t_infos *infos);
//[----------------end of paths.c----------------]

/*
** Finds the correct builtins function and lauchs it
*/
int			choose_builtin(t_infos *infos, t_cmd *cmd);

//builtins functions
int			mini_unset(t_infos *infos, t_cmd *cmd);
int			mini_export(t_infos *infos, t_cmd *cmd);
void		print_export(t_infos *infos);
int			mini_cd(t_infos *infos, t_cmd *cmd);
int			mini_echo(t_infos *infos, t_cmd *cmd);
int			mini_env(t_infos *infos, t_cmd *cmd);
int			mini_exit(t_infos *infos, t_cmd *cmd);
int			mini_pwd(t_infos *infos, t_cmd *cmd );

//functions to test the builtins (to be removed)
void		test_unset(t_infos *infos);
void		test_env(t_infos *infos);
void		test_echo(void);
void		test_pwd(void);
void		test_cd(t_infos *infos);
void		test_export(t_infos *infos);

/*
** SIGNALS
*/
void		sigint_handler(int status);
void		sigquit_handler(int signal);

/*
** Error
*/
void		print_error(int state, t_infos *infos);

#endif
