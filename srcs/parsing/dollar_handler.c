#include "../includes/minishell.h"

static char	*get_dollar_value_2(t_infos *info, char *temp, char *ret, int i)
{
	int	size;
	int	j;
	int	counter;

	if (!(ft_strncmp(temp, info->envs[i], ft_strlen(temp))))
	{
		size = ft_strlen(info->envs[i]) - ft_strlen(temp);
		ret = (char *)malloc(sizeof(char) * (size + 1));
		if (ret == NULL)
			print_error(E_MALLOC, info);
		j = 0;
		while (info->envs[i][j] != '=' || info->envs[i][j] != '\0')
			j++;
		counter = -1;
		j++;
		while (info->envs[i][j])
		{
			ret[++counter] = info->envs[i][j];
			j++;
		}
		ret[counter] = '\0';
		return (ret);
	}
	return (NULL);
}

char	*get_dollar_value(t_infos *info, char *str)
{
	int		i;
	char	*ret;
	char	*temp;

	ret = NULL;
	temp = ft_strjoin(str, "=");
	i = -1;
	while (info->envs[++i])
	{
		ret = get_dollar_value_2(info, temp, ret, i);
	}
	if (ret == NULL)
		ret = ft_strdup("");
	free(temp);
	return (ret);
}

char	*check_dollar_ret_val(char *value)
{
	char	**temp;
	int		i;
	int		len;

	i = -1;
	temp = ft_split(value, ' ');
	free(value);
	value = ft_strdup("");
	while (temp[++i])
	{
		if (ft_isallspace(temp[i]))
			value = merge_content(value, temp[i], 1);
	}
	len = ft_strlen(value);
	if (len > 0)
		value[len - 1] = '\0';
	if (len == 0)
		value[len] = '\0';
	free_doub_char(temp);
	return (value);
}

char	*check_dollar_arg(t_infos *info, char *arg)
{
	char	**temp_args;
	char	*value;
	char	*content;
	int		i;

	i = 1;
	temp_args = ft_split(arg, '$');
	content = ft_strdup(temp_args[0]);
	while (temp_args[i])
	{
		value = get_dollar_value(info, temp_args[i]);
		value = check_dollar_ret_val(value);
		content = merge_content(content, value, 0);
		free(value);
		i++;
	}
	free_doub_char(temp_args);
	return (content);
}
