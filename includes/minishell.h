/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avogt <avogt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:57:49 by avogt             #+#    #+#             */
/*   Updated: 2021/10/30 21:23:53 by avogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <curses.h>
# include <signal.h>
# include <term.h>
# include "libft.h"

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
	int				here_doc;
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
	int				parse_error;
	struct s_token	*tokens;
	struct s_cmd	*commands;
	struct s_cmd	*first_cmd;
	struct s_env	*first_env;
	char			**envs;
}					t_infos;

/*
** Free functions
*/
void		free_infos(t_infos *infos);
void		free_tokens(t_infos *info);
void		ft_free_tab_ptr(char **ptr);
void		free_env_list(t_infos *infos);
void		free_red_tokens(t_cmd *com);
void		free_cmnds(t_infos *info);

/*
** parsing.c
*/
void		start_parsing(t_infos *info);
void		free_cmnds(t_infos *info);

/*
** parsing_init.c 6 functions
*/
void		get_token_type(t_token *new, t_infos *info, int i);
t_token		*token_init(void);
void		lst_add_back(t_infos *info, t_token *new);
t_token		*ft_lstlast_token(t_token *lst);
void		add_to_struct(t_infos *info);

/*
** lexer.c
*/
void		merge_same(t_infos *info);
void		merge_tokens(t_infos *info, int start, int total);
t_token		*join_tokens(t_token *tokens);
void		update_tokens_pos(t_infos *info);

/*
** parsing_utils.c
*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isspace_isdigit(char c, char d);
char		*char_to_str(char c, t_infos *info);
char		*remove_space_digit(char *line, char c);
int			ft_isallspace(char *line);

/*
** dollar_parser.c
*/
void		get_dollar(t_infos *info);
void		update_dollar_type(t_infos *info, int pos);
void		get_dollar_prev(t_infos *info);

/*
** dollar_expander.c (expand dollar above 25)
*/
char		*get_dollar_value_help(int size, char *env, t_infos *info);
char		*get_dollar_value(t_infos *info, char *str);
char		*check_dollar_arg(t_infos *info, char *arg);
void		expand_dollar(t_infos *info);

/*
** dollar_handler.c
*/
int			is_all_numdigit(char *str);
char		*join_double_char(char **args);
char		*get_word(char *word, int size, int start, int end, t_infos *info);
char		*check_special_char(t_infos *info, char *content, char *word);
char		*check_dollar_ret_val(char *value);
char		*handle_question(t_infos *info, char *content, char *word);

/*
** quotes_handler.c
*/
int			closing_quote_helper(t_token *temp, int mode);
int			check_closing_quote(t_infos *info, int pos, int mode);
int			handle_double_quote(t_token *token, t_infos *info);
int			handle_single_quote(t_token *token, t_infos *info);
void		check_quotes(t_infos *info);

/*
** quotes_utils.c
*/
char		*update_quotes_content(t_token *temp, t_infos *info);
int			check_dollar(char *content);
void		update_token_type(t_infos *info, char *from, char *to);

/*
** redirections.c
*/
int			here_doc_exec(char *str);
void		here_doc_ctrl_c(int status);
int			check_for_ctrl_c(void);
int			check_redirections(t_token *red, t_cmd *cmd, t_infos *info);
int			last_here_doc(t_cmd *cmd, char *str);
int			handle_here_doc(t_cmd *cmd, int pos, t_infos *info);
void		handle_infile(char *infile, t_cmd *cmd, int pos, t_infos *info);
void		handle_outfile(char *outfile, char *type,
				t_cmd *cmd, t_infos *info);
void		handle_redirections(t_infos *info);

/*
** redirections_utils.c
*/
int			check_last_input_red(t_cmd *cmd, int pos);
int			fd_write(int fd, char *line);

/*
** files_parser.c
*/
void		get_outfile(t_token *temp, t_infos *info);
void		get_infile(t_token *temp, t_infos *info);
void		parse_outfile(t_infos *info);
void		parse_infile(t_infos *info);

/*
** libft_utils.c
*/
char		**ft_split(char *str, char c);
void		free_doub_char(char **str);
char		*join_double_char(char **args);

/*
** commands_init.c
*/
t_cmd		*ft_lstlast_cmd(t_cmd *lst);
void		red_lst_add_back(t_cmd *cmd, t_token *new);
void		cmd_lst_add_back(t_cmd *cmd, t_infos *info);
void		*cmnd_init(void);

/*
** token_to_cmd.c
*/
void		fill_redirections(t_token *tokens, t_cmd *cmd, t_infos *info);
int			get_cmd_args_num(t_infos *info, int start, int end);
char		**get_cmd_args(t_infos *info, int start, int end);
void		fill_cmd(t_infos *info, int start, int end, t_cmd *cmd);
void		move_to_cmd(t_infos *info);

/*
** token_to_cmd_utils.c
*/
char		*remove_last_space(char *str);
char		*merge_content(char *str, char *content, int space);
int			check_builtin(char *str);
void		fill_red_pos(t_cmd *cmd);
void		fill_cmd_info(t_infos *info);

/*
** print_temp.c Temp Function to be removed later
*/
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
char		*get_exit_code(void);

int			add_layer_shlvl(t_infos *infos);
void		print_env_tab(t_infos *infos);
char		**add_env_tab(char **envs, char *key_value_str);
int			change_line_env_tab(t_infos *infos, char *key, char *value);
int			remove_env_tab(t_infos *infos, char *key);
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
void		ignore_signals(void);
void		ignore_all_signals(void);
void		set_signals(void);

/*
** Error
*/
void		print_error(int state, t_infos *infos);
void		print_bash_error(int state, t_cmd *cmd);
void		free_chars_bash_error(char *s, char *s1, char *s2, char *s3);
void		close_child_fd_error(t_cmd *cmd);
void		print_parsing_error(int state, t_infos *infos);
void		print_pipe_error(int state, t_infos *info);

void		minishell(t_infos *infos, int int_mode);
int			check_valid_identifier(char *arg);
int			check_tab_identifier(char **key_value_tab, char *str);
char		*join_args(t_cmd *cmd, t_infos *infos);

int			*get_error_code(void);
void		set_error_code(int status);
int			*get_interruption(void);
void		set_interruption(int status);

#endif
