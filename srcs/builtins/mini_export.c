#include "../../includes/minishell.h"

/*
**
** Export without arg - print in ascii order the tab of ptrs with some changes
** 1. It displays the word "export" followed by a whitespace
** 2. It displays the key
** 3. It displays a opening double quote
** 4. It displays all the values of the key
** 5. It displays the closing double quote
** 6. It displays '\n'
**
*/
static int	print_line(t_infos *infos, int index)
{
	char	*key;
	char	*value;
	char	*final_str;

	key = get_key(infos, index);
	value = get_value(infos, key);
	if (!key || !value)
		return (0);
	final_str = (char *)malloc(sizeof(char) *
			(ft_strlen(key) + ft_strlen(value) + 11));
	if (!final_str)
		return (0);
	final_str[0] = '\0';
	final_str = ft_strcat(final_str, "export ");
	final_str = ft_strcat(final_str, key);
	final_str = ft_strcat(final_str, "=");
	final_str = ft_strcat(final_str, "\"");
	final_str = ft_strcat(final_str, value);
	final_str = ft_strcat(final_str, "\"");
	ft_putendl_fd(final_str, STDOUT_FILENO);
	free(key);
	free(value);
	free(final_str);
	return (1);
}

static int	print_asci_order(t_infos *infos, int num)
{
	int	i;
	int tmp;
	int	index;

	index = 0;
	i = 0;
	while (i < num)
	{
		tmp = 0;
		while  (tmp < num)
		{
			tmp++;
		}
		i++;
	}
	return (1);
}

void	print_export(t_infos *infos)
{
	int	number_env;
	int	i;

	i = 0;
	if (!infos->envs)
		return ;
	while (infos->envs[i])
		i++;
	number_env = i;
	print_asci_order(infos, number_env);
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
	key_value_tab = ft_split_char(cmd->arg[1], '='); // we're only interested in the first (the key)
	ret_find_path = find_pos_key(infos, key_value_tab[0]);
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
