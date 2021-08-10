#include "../../includes/minishell.h"

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
**
*/

int	mini_cd(t_infos *infos, t_cmd *cmd)
{
	char	*old_path;
	char	*current_path;
	char	*path;
	int		ret;
	int		ret_change_line[2];

	old_path = getenv("PWD");
	if (cmd->arg[1] == NULL)
		path = getenv("HOME");
	else
		path = cmd->arg[1];
	if (chdir(path))
		ret = 0;
	else
	{
		ret = 1;
		current_path = getenv("PWD");
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
**

void	test_cd(t_infos *infos)
{
	int		ret_mini_cd;
	int		i;
	char	*path[6];

	i = 0;
	path[0] = "srcs";
	path[1] = "../..";
	path[2] = "./minishell/includes";
	path[3] = "/";
	path[4] = "./home/user42/minishell";
	path[5] = NULL;
	while (path[i])
	{
		ret_mini_cd = mini_cd(infos, );
		test_pwd();
		if (!ret_mini_cd)
			ft_putendl_fd("cd error", STDERR_FILENO);
		i++;
	}
	print_env_tab(infos);
}
*/
