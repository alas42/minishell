/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:49 by avogt             #+#    #+#             */
/*   Updated: 2021/10/21 23:46:19 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//#include <editline/readline.h>
//#include <editline/history.h>

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

typedef struct s_token
{
	int				pos;
	char			*content;
	char			*type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	int				index;
	int				builtin;
	int				process;
	int				pipe_in;
	int				pipe_out;
	int				fd_infile;
	int				fd_outfile;
	int				here_doc_count;
	char			*name_infile;
	char			*name_outfile;
	char			**arg;
	struct s_token	*redirection;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

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
	struct s_cmd	*commands;
	struct s_cmd	*first_cmd;
	struct s_env	*first_env;
	char			**envs;
	int				last_return_code;
}					t_infos;

/*
** Free functions
*/
void		free_infos(t_infos *infos);
void		free_tokens(t_infos *info);
void		free_cmd_list(t_infos *infos);
void		ft_free_tab_ptr(char **ptr);
void		free_env_list(t_infos *infos);
void		free_red_tokens(t_cmd *com);
void		free_cmnds(t_infos *info);

//parsing.c
void		start_parsing(t_infos *info);
void		free_cmnds(t_infos *info);

//lexer.c
void		merge_same(t_infos *info);
void		merge_tokens(t_infos *info, int start, int total);
t_token		*join_tokens(t_token *tokens);
void		update_tokens_pos(t_infos *info);

//parsing_init.c
void		get_token_type(t_token *new, t_infos *info, int i);
t_token		*token_init(void);
void		lst_add_back(t_infos *info, t_token *new);
t_token		*ft_lstlast_token(t_token *lst);
void		add_to_struct(t_infos *info);
t_cmd		*ft_lstlast_cmd(t_cmd *lst);

//parsing_utils.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isspace_isdigit(char c, char d);
char		*char_to_str(char c);
char		*remove_space_digit(char *line, char c);
int			ft_isallspace(char *line);

//token_handler.c
void		handle_output_red(t_infos *info);
void		handle_input_red(t_infos *info);

//token_handler_utils.c
char		**ft_split(char *str, char c);
void		free_doub_char(char **str);

//dollar_handler.c
void    	expand_dollar(t_infos *info);
void		get_dollar(t_infos *info);
void    	update_dollar_type(t_infos *info, int pos);
void		get_dollar_prev(t_infos *info);

//quotes_handler.c
void		check_quotes(t_infos *info);

//token_utils.c
void		*cmnd_init(void);
void		cmd_lst_add_back(t_cmd *cmd, t_infos *info);

//redirections.c
void	handle_redirections(t_infos *info);

//token_to_cmd.c
void		move_to_cmd(t_infos *info);
char		*merge_content(char *str, char *content, int space);
void		red_lst_add_back(t_cmd *cmd, t_token *new);

//print_temp.c Temp Function to be removed later
void		print_info(t_infos *info);
void		print_token_list(t_token *token);
void		print_cmnd_single(t_cmd *cmd);
void		print_cmnds(t_infos *info);

/*
** UTILS FOR THE INFOS STRUCTURE
*/
/*
** Clear the structures before another loop
*/
void		clear_infos(t_infos *infos);
/*
** Free some data from the infos structure before another loop
*/
void		reinit_infos(t_infos *infos);
t_infos		*init_infos(char **envp);

/*
** Returns the command associated with infos->index_cmd
** Returns Null if no command is found
*/
t_cmd		*get_cmd(t_infos *infos);
int			child_fds(t_infos *infos, t_cmd *cmd);
int			parent_fds(t_infos *infos, t_cmd *cmd);
int			exec_cmds(t_infos *infos);
int			loop_through_cmds(t_infos *infos);

/*
** Utils for environment variables (tab)
*/
char		**get_env_tab(char **envp);
char		*get_value(t_infos *infos, char *key);
char		*get_key(t_infos *infos, int index);
char		*get_line(t_infos *infos, int index);
char		*get_exit_code(t_infos *infos);

int			add_layer_shlvl(t_infos *infos);
void		print_env_tab(t_infos *infos);
char		**add_env_tab(char **envs, char *key_value_str);
int			change_line_env_tab(t_infos *infos, char *key, char *value);
char		**remove_env_tab(t_infos *infos, char *key);
char		*create_pair_key_value(char *key, char *value);
/*
** Returns the index from the environment variable to_find in the tab
*/
int			find_pos_key(t_infos *infos, char *to_find);

/*
** Add a path string from environment table to the name of the executable given
*/
int			add_path(char **arg, char *path, int len_path);

/*
** Checks if the paths given corresponds to an existing file
*/
int			ft_exists(char *file_path);

/*
** Loops until the correct path if found
*/
void		check_paths(t_infos *infos);

/*
** Finds the correct builtins function and lauchs it
*/
int			choose_builtin(t_infos *infos, t_cmd *cmd);

/*
** Builtins functions
*/
int			mini_unset(t_infos *infos, t_cmd *cmd);
int			mini_export(t_infos *infos, t_cmd *cmd);
void		print_export(t_infos *infos);
int			mini_cd(t_infos *infos, t_cmd *cmd);
int			mini_echo(t_infos *infos, t_cmd *cmd);
int			mini_env(t_infos *infos, t_cmd *cmd);
int			mini_exit(t_infos *infos, t_cmd *cmd);
int			mini_pwd(t_infos *infos, t_cmd *cmd );
int			solo_builtin(t_infos *infos, t_cmd *cmd);

/*
** SIGNALS
*/
void		sigint_handler(int status);
void		sigquit_handler(int signal);

/*
** Error
*/
void		print_error(int state, t_infos *infos);
void		print_bash_error(int state, t_cmd *cmd);

void		minishell(t_infos *infos, int int_mode);

#endif
