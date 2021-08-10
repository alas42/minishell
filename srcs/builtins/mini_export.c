#include "../../includes/minishell.h"

char	*create_pair_key_value(char *key, char *value)
{
	char	*key_value_str;
	size_t	length;

	length = ft_strlen(key) + ft_strlen(value) + 4;
	key_value_str = (char *)malloc(sizeof(char) * (length));
	key_value_str[0] = '\0';
	key_value_str = ft_strcat(key_value_str, key);
	key_value_str = ft_strcat(key_value_str, "=");
	key_value_str = ft_strcat(key_value_str, value);
	key_value_str = ft_strcat(key_value_str, "\0");
	return (key_value_str);
}

/*
**
** Export without arg - print in ascii order the tab of ptrs with TWO change
** 1. It displays with double quotes around the value ... it means we have
** to cut the string in two and add quotes around the second string obtained
** before printing
** 2. It displays the lists with 'export ' before every line
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

	env = infos->first_env;
	while (env)
	{
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

int	mini_export(t_infos *infos, char *key, char *value)
{
	int		ret_find_path;
	char	*key_value_str;

	if (key == NULL && value == NULL)
		print_export(infos);
	key_value_str = create_pair_key_value(key, value);
	ret_find_path = find_pos_key(infos, key);
	if (ret_find_path > -1)
	{
		free(infos->envs[ret_find_path]);
		infos->envs[ret_find_path] = key_value_str;
	}
	else
		infos->envs = add_env_tab(infos->envs, key_value_str);
	return (1);
}

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
}
