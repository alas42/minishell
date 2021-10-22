#include "../includes/minishell.h"

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

// echo "$one$two$three"
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
		value = get_dollar_value(info, temp_args[i]);
		content = merge_content(content, value, 0);
		free(value);
		i++;
	}
	free_doub_char(temp_args);    
	return(content);
}

void    expand_dollar(t_infos *info)
{
	t_token     *token;
	char        **arg;
	char        *ret_val;
	int         i;
	int         j;
	int         counter;
	
	i = 0;
	counter = 0;
	token = info->tokens;
	ret_val = NULL;
	while (token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
		{
			ret_val = check_dollar_arg(info, token->content);
			free(token->content);
			token->content = ft_strdup(ret_val);
			free(ret_val);
			free(token->type);
			token->type = ft_strdup("literal");
		}
		else if (!(ft_strcmp(token->type, "literal_dollar")))
		{
			arg = ft_split(token->content, ' ');
			free(token->content);
			token->content = ft_strdup("");
			while(arg[i])
			{
				j = 0;
				while (arg[i][j])
				{
					if (arg[i][j] == '$')
					{
						ret_val = check_dollar_arg(info, arg[i]);
						token->content =  merge_content(token->content, ret_val, 1);
						free(ret_val);
						counter = 1;
						break;
					}
					j++;
				}
				if (counter == 0)
					token->content = merge_content(token->content, arg[i], 1);
				counter = 0;
				i++;
			}
			free(token->type);
			token->type = ft_strdup("literal");
			free_doub_char(arg);
		}
		token = token->next;
	}
}

void    get_dollar_prev(t_infos *info)
{
	t_token *token;

	token = info->tokens;
	while(token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
		{
			if(token->prev != NULL && !(ft_strcmp(token->prev->type, "literal")))
				merge_tokens(info, token->prev->pos, 1);
		}
		token = token->next;
	}
}

void    update_dollar_type(t_infos *info, int pos)
{
	t_token *temp;
	int     i;

	i = 0;
	temp = info->tokens;
	while (i < pos)
	{
		temp = temp->next;
		i++;
	}
	free(temp->type);
	temp->type = ft_strdup("dollar");
}

void    get_dollar(t_infos *info)
{
	t_token *temp;
	int     i;

	i = 0;
	temp = info->tokens;
	while (temp && (ft_strcmp(temp->type, "pipe")))
	{
		if (ft_strcmp(temp->type, "dollar") == 0)
		{
			if (temp->next != NULL && !(ft_strcmp(temp->next->type, "literal")))
			{
				merge_tokens(info, i, 1);
				update_dollar_type(info, i);
				temp = info->tokens;
				i = 0;
			}
		}
		i++;
		temp = temp->next;
	}
}