#include "../../includes/minishell.h"

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
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

static char	*get_actual_path(void)
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

int	mini_cd(t_infos *infos, t_cmd *cmd)
{
	char	*old_path;
	char	*current_path;
	char	*path;
	int		ret;
	int		ret_change_line[2];

	old_path = get_value(infos, "PWD");
	if (cmd->arg[1] == NULL)
		path = get_value(infos, "HOME");
	else
		path = cmd->arg[1];
	if (chdir(path))
		ret = 0;
	else
	{
		ret = 1;
		current_path = get_actual_path();
		ret_change_line[0] = change_line_env_tab(infos, "OLDPWD", old_path);
		ret_change_line[1] = change_line_env_tab(infos, "PWD", current_path);
		if (!ret_change_line[0] || !ret_change_line[1])
			ret = 0;
		free(current_path);
	}
	free(old_path);
	return (ret);
}

/*
**
** Tests all paths contained in *path[] one after another
** And calls to mini_pwd to print where the terminal is


void	test_cd(t_infos *infos)
{
	char	**cmd1;
	t_cmd	*cmd01;
	cmd1 = ft_split_char("cd srcs", ' ');
	cmd01 = creating_cmd(cmd1, 0, 1);
	char	**cmd2;
	char	**cmd3;
	char	**cmd4;

	t_cmd	*cmd02;
	t_cmd	*cmd03;
	t_cmd	*cmd04;


	cmd2 = ft_split_char("cd ../..", ' ');
	cmd3 = ft_split_char("cd ./minishell/includes", ' ');
	cmd4 = ft_split_char("cd /", ' ');

	cmd02 = creating_cmd(cmd2, 1, 1);
	cmd03 = creating_cmd(cmd3, 1, 1);
	cmd04 = creating_cmd(cmd4, 1, 0);
	int		ret_mini_cd;

	ret_mini_cd = mini_cd(infos, cmd01);
	if (!ret_mini_cd)
		ft_putendl_fd("cd error", STDERR_FILENO);
	ret_mini_cd = mini_cd(infos, cmd02);
	if (!ret_mini_cd)
		ft_putendl_fd("cd error", STDERR_FILENO);
	ret_mini_cd = mini_cd(infos, cmd03);
	if (!ret_mini_cd)
		ft_putendl_fd("cd error", STDERR_FILENO);
	ret_mini_cd = mini_cd(infos, cmd04);
	if (!ret_mini_cd)
		ft_putendl_fd("cd error", STDERR_FILENO);
	print_env_tab(infos);
}
*/
