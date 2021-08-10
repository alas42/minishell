#include "../../includes/minishell.h"

/*
**
** Export without arg - print in ascii order the tab of ptrs with some changes
** 1. It displays export
** 2. It displays a whitespace
** 3. It displays the key
** 4. It displays a double quote
** 5. It displays all the values
** 6. It displays a double quote
** 7. It displays '\n'
**
** That's why I thought about a chained list with an integer
** containing positions.
** It can be very good if the char * in every nodes points to
** according char * in the tab
**
*/

static void	print_export(t_infos *infos)
{
	t_env	*env;
	//char	**key_value_tab;

	env = infos->first_env;
	while (env)
	{
		//key_value_tab = get;
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putendl_fd(env->pair, STDOUT_FILENO);
		env = env->next;
	}
}

/*
**
** NOT TO FORGET : SET CORRECT RETURN STATUS CODE
** USING : tab of pointers and not list
**
*/

int	mini_export(t_infos *infos, t_cmd *cmd)
{
	int		ret_find_path;
	char	**key_value_tab;

	if (!cmd->arg[1])
	{
		print_export(infos);
		return (1);
	}
	key_value_tab = ft_split_char(cmd->arg[1], '='); //FALSE it cannot be done this way, the value themselves can contain the char '='
	ret_find_path = find_pos_key(infos, tab[0]);
	if (ret_find_path > -1)
	{
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = ft_strdup(cmd->arg[1]);
	}
	else
		infos->envs = add_env_tab(infos->envs, cmd->arg[1]);
	ft_free_tab_ptr(key_value_tab);
	return (1);
}

/*
void	test_export(t_infos *infos)
{
	char	*key;
	char	*value;
	char	*key2;
	char	*value2;

	key = "test_key";
	key2 = "testare_key";
	value = "value2_key";
	value2 = "oazkdozak";
	ft_putendl_fd("\n\n", STDOUT_FILENO);
	mini_export(infos, key, value);
	mini_export(infos, key2, value2);
	print_env_tab(infos);
	ft_putendl_fd("\n\n", STDOUT_FILENO);
}*/
