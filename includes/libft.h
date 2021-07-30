#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 1024

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;


float	ft_atof(const char *str, size_t *i);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_strdel(char **as);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
int		get_next_line(int fd, char **line);

#endif
