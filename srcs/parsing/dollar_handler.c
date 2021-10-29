#include "../includes/minishell.h"

int		is_all_numdigit(char *str)
{
	int		i;

	i = 0;
	while(str[i])
	{
		if (!(ft_isalpha(str[i])) && !(ft_isdigit(str[i])))
			return (i);
		i++;
	}
	return (0);
}


char    *get_dollar_value(t_infos *info, char *str)
{
	int     i;
	int     j;
	int     counter;
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
			ret = (char *)malloc(sizeof(char) * (size + 1));
			if (ret == NULL)
				printf("malloc error in get dolalr value\n");
			j = 0;
			while (info->envs[i][j] != '=' || info->envs[i][j] == '\0')
				j++;
			counter = 0;
			j++;
			while(info->envs[i][j])
			{
				ret[counter] = info->envs[i][j];
				j++;
				counter++;
			}
			ret[counter] = '\0';
		}
		i++;
	}
	if (ret == NULL)
		ret = ft_strdup("");
	free(temp);
	return (ret);
}

char	*check_dollar_ret_val(char *value)
{
	char 	**temp;
	int		i;
	int		len;

	i = -1;
	temp = ft_split(value, ' ');
	free(value);
	value = ft_strdup("");
	while(temp[++i])
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


char	*get_word(char *word, int size, int start, int end)
{
	// printf("word [%s]\n", word);
	// printf("size [%d]\n", size);
	// printf("start [%d]\n", start);
	// printf("end [%d]\n", end);

	char *str;
	int		i;

	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		printf("Malloc error\n");
	if (end < 0)
		end = ft_strlen(word);
	i = 0;
	while(start < end)
	{
		str[i] = word[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);

}
/*
echo "hello prev$USER'this_should_print hello"
*/

char	*check_special_char(t_infos *info, char *content, char *word)
{
	char	*dollar;
	char	*rest;
	char	*value;
	int		i;
	int		j;

	(void)info;
	i = 0;
	while(word[i])
	{
		if (!(ft_isalpha(word[i])) && !(ft_isdigit(word[i])))
			break;
		i++;
	}
	j = (ft_strlen(word) - i) + 1;
	dollar = get_word(word, i + 1, 0, i);
	rest = get_word(word, j, i, -1);
	value = get_dollar_value(info, dollar);
	value = check_dollar_ret_val(value);
	value = merge_content(value, rest, 0);
	free(rest);
	content = merge_content(content, value, 0);
	free(value);
	free(dollar);
	return (content);
}


// echo "$one$two$three"
char    *check_dollar_arg(t_infos *info, char *arg)
{
	char    **temp_args;
	char    *value;
	char    *content;
	int     i;
	int		ret;

	ret = -1;
	i = 1;
	temp_args = ft_split(arg, '$');
	content = ft_strdup(temp_args[0]);
	while (temp_args[i])
	{
		ret = is_all_numdigit(temp_args[i]);
		if (ret == 0)
		{
			value = get_dollar_value(info, temp_args[i]);
			value = check_dollar_ret_val(value);
			content = merge_content(content, value, 0);
			free(value);
		}
		else
		{
			content = check_special_char(info, content, temp_args[i]);
		}
		i++;
	}
	free_doub_char(temp_args);
	return(content);
}

/*
echo "$a"$b"this$a hekk"wow$b
*/

char	*join_double_char(char **args)
{
	int		i;
	char 	*temp;

	i = -1;
	temp = ft_strdup("");
	while(args[++i])
		temp = merge_content(temp, args[i], 1);
	temp = remove_last_space(temp);
	return(temp);
}





