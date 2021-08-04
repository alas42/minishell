#include "../../includes/minishell.h"

/*
**
** Print the content of env in alphabetical order
** That is if export is used without an assignation key=value
**
*/

static void	print_export(t_infos *infos)
{
	t_env	*env;

	env = infos->first_env;
	while (env)
	{
		ft_putendl_fd(env->pair, STDOUT_FILENO);
		env = env->next;
	}
}

static int	mini_export(t_infos *infos, char *key, char *value)
{
	int		i;
	int		ret_find_path;
	char	*key_value_str;
	t_env	*env;

	if (key == NULL && value == NULL)
		print_export(infos);
	i = 0;
	ret_find_path = 0;
	env = infos->first_env;
	ret_find_path = find_pos_key(infos, value);
	if (ret_find_path > -1)
	{
		while (i++ < ret_find_path)
			env = env->next;
		free(env->pair);
		key_value_str = (char *)malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value) + 4));
		key_value_str[0] = '\0';
		key_value_str = ft_strcat(key_value_str, key);
		key_value_str = ft_strcat(key_value_str, "=\"");
		key_value_str = ft_strcat(key_value_str, value);
		key_value_str = ft_strcat(key_value_str, "\"\0");
		env->pair = key_value_str;
		return (1);
	}
	print_export(infos);
	return (0);
}

void	test_export(t_infos *infos)
{
	char	*key;
	char	*value;

	key = "test_key";
	value = "value_key";
	mini_export(infos, key, value);
}
