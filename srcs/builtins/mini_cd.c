#include "../../includes/minishell.h"

/*
**
** WHAT NOT TO FORGET:
** changing OLDPWD and PWD in env variables (once I know how to do it)
** what happens when getenv returns null (if no env variable ?)
** 
**
** Should we do ~ and - when subjects says ONLY relatives and absolutes paths without any mentions to options and arguments ?
** IF not, it is too easy ... right ?
**
*/

int		mini_cd(char *path)
{
	char	*current_path;
	int		ret;

	current_path = mini_pwd(); //not used yet, careful
	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path))
	{
		ret = 0;
	}
	ret = 1;
	free(current_path);
	return (ret);
}

void	test_cd(void)
{
	int		ret_mini_cd;
	int		i;
	char	*path[5];

	i = 0;
	path[0] = "srcs"; 
	path[1] = "../..";
	path[2] = "./minishell/includes";
	path[3] = "/";
	path[4] = NULL;
	while (path[i])
	{
		ret_mini_cd = mini_cd(path[i]);
		test_pwd();
		if (!ret_mini_cd)
			ft_putendl_fd("cd error", STDERR_FILENO);
		i++;
	}
}
