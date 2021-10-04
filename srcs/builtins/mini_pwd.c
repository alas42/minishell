#include "../../includes/minishell.h"

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

int	mini_pwd(t_infos *infos, t_cmd *cmd)
{
	char	*path_dir;
	size_t	length_path;
	char	*ret;

	ret = 0;
	length_path = 1024;
	path_dir = (char *)malloc(sizeof(char) * length_path);
	if (!path_dir)
		return (0);
	ret = getcwd(path_dir, length_path);
	while (errno == ERANGE)
	{
		path_dir = realloc_path_dir(path_dir, &length_path);
		if (!path_dir)
			return (0);
		ret = getcwd(path_dir, length_path);
		if (ret)
			break ;
	}
	ft_putendl_fd(free_and_return(path_dir, ret), STDOUT_FILENO);
	return (1);
	(void)infos;
	(void)cmd;
}
