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


typedef struct s_token
{
	int				pos;
	char			*content;
	char			*type;
	struct 	s_token	*next;
	struct	s_token	*prev;
}				t_token;

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
	struct	s_token	*tokens;
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
void	check_paths(t_infos *infos);
void	ft_free_tab_ptr(char **ptr);
int		exec_cmds(t_infos *infos, char **envp);
t_cmd	*get_cmd(t_infos *infos);
void	tests_exec_cmds(t_infos *infos, char **envp);

//free.c
void	free_infos(t_infos *infos);
void	free_tokens(t_infos *info);

//parsing.c
void    start_parsing(t_infos *info);

//lexer.c
void    	merge_same(t_infos *info);
void    	merge_tokens(t_infos *info, int start, int total);
t_token     *join_tokens(t_token *tokens);
void    update_tokens_pos(t_infos *info);

//parsing_init.c
void    	get_token_type(t_token *new, t_infos *info, int i);
t_token  	*token_init();
void    	lst_add_back(t_infos *info, t_token *new);
t_token		*ft_lstlast(t_token *lst);
void   		add_to_struct(t_infos *info);

//parsing_utils.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isspace_isdigit(char c, char d);
char    	*char_to_str(char c);


//print_temp.c Temp Function to be removed later
void    	print_info(t_infos *info);
void		print_token_list(t_token *token);

#endif