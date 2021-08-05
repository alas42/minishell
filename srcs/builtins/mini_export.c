#include "../../includes/minishell.h"

static char *create_pair_key_value(char *key, char *value)
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
** Env builtin print it exactly like this
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
	mini_export(infos, key, value);
	mini_export(infos, key2, value2);
	print_env_tab(infos);
}
