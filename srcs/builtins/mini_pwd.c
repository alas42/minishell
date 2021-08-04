#include "../../includes/minishell.h"

/*
**
** For now, it is putting the result of getcwd() in path_dir
**
** Step 1: Check if the error is about space needed in the char *
** Step 2.a: If yes, realloc with more
** Step 2.b: If not return with 0, telling the function failed
** Step 3: If no error, pwd works and the str contains the full path requested
**
** Results:
** Are returned as a malloced char * or NULL pointer
**
*/

static char	*free_and_return(char *path_dir, char *ret)
{
	if (!ret)
	{
		if (path_dir)
			free(path_dir);
		return (NULL);
	}
	return (path_dir);
}

static char	*realloc_path_dir(char *path_dir, size_t *length_path)
{
	free(path_dir);
	*length_path = *length_path * 2;
	path_dir = (char *)malloc(sizeof(char) * *length_path);
	if (!path_dir)
		return (NULL);
	return (path_dir);
}


char	*mini_pwd(void)
{
	char	*path_dir;
	size_t	length_path;
	char	*ret;

	ret = 0;
	length_path = 1024;
	path_dir = (char *)malloc(sizeof(char) * length_path);
	if (!path_dir)
		return (NULL);
	ret = getcwd(path_dir, length_path);
	while (errno == ERANGE)
	{
		path_dir = realloc_path_dir(path_dir, &length_path);
		if (!path_dir)
			return (NULL);
		ret = getcwd(path_dir, length_path);
		if (ret)
			break ;
	}
	return (free_and_return(path_dir, ret));
}

void	test_pwd(void)
{
	char *ret_mini_pwd;

	ret_mini_pwd = mini_pwd();
	if (ret_mini_pwd)
	{
		ft_putendl_fd(ret_mini_pwd, STDOUT_FILENO);
		free(ret_mini_pwd);
	}
	if (!ret_mini_pwd)
		ft_putendl_fd("pwd error", STDERR_FILENO);
}
