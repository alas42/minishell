#include "../includes/minishell.h"

char	*get_dollar_value_help(int size, char *env, t_infos *info)
{
	int		j;
	int		i;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		print_error(E_MALLOC, info);
	j = 0;
	while (env[j] != '=' || env[j] == '\0')
		j++;
	j++;
	i = 0;
	while(env[j])
	{
		ret[i] = env[j];
		j++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char    *get_dollar_value(t_infos *info, char *str)
{
	int     i;
	char    *ret;
	int     size;
	char    *temp;

	ret = NULL;
	temp = ft_strjoin(str, "=");
	i = 0;
	while (info->envs[i])
	{
		if (!(ft_strncmp(temp, info->envs[i], ft_strlen(temp))))
		{
			size = ft_strlen(info->envs[i]) - ft_strlen(temp);
			ret = get_dollar_value_help(size, info->envs[i], info);
		}
		i++;
	}
	if (ret == NULL)
		ret = ft_strdup("");
	free(temp);
	return (ret);
}

char    *check_dollar_arg(t_infos *info, char *arg)
{
	char    **temp_args;
	char    *value;
	char    *content;
	int     i;

	i = 1;
	temp_args = ft_split(arg, '$');
	content = ft_strdup(temp_args[0]);
	while (temp_args[i])
	{
		if (is_all_numdigit(temp_args[i]) == 0)
		{
			value = get_dollar_value(info, temp_args[i]);
			value = check_dollar_ret_val(value);
			content = merge_content(content, value, 0);
			free(value);
		}
		else if (is_all_numdigit(temp_args[i]) == 1)
			content = check_special_char(info, content, temp_args[i]);
		else
			content = handle_question(info, content, temp_args[i]);
		i++;
	}
	free_doub_char(temp_args);
	return(content);
}

void	expand_dollar(t_infos *info)
{
	t_token	*token;
	char	**temp_args;
	char	*ret;
	int		i;

	token = info->tokens;
	while(token)
	{
		if (!(ft_strcmp(token->type, "literal_dollar"))
			|| !(ft_strcmp(token->type, "dollar")))
		{
			temp_args = ft_split(token->content, ' ');
			i = -1;
			while(temp_args[++i])
			{
				ret = check_dollar_arg(info, temp_args[i]);
				free(temp_args[i]);
				temp_args[i] = ret;
			}
			free(token->content);
			token->content = join_double_char(temp_args);
			free(token->type);
			token->type = ft_strdup("literal");
			free_doub_char(temp_args);
		}
		token = token->next;
	}
}

