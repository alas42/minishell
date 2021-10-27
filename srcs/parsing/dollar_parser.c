#include "../includes/minishell.h"

//checks and merge the word before the $. [t][h][e][$one] = [the$one]
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

//change the pos token type to dollar
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

//Get the keyword of dollar. [$][o][n][e] = [$one] {type dollar}
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

void	expand_dollar(t_infos *info)
{
	t_token	*token;
	char	**temp_args;
	char	*ret;
	int		i;

	token = info->tokens;
	temp_args = NULL;
	ret = NULL;
	while(token)
	{
		if (!(ft_strcmp(token->type, "literal_dollar")) ||
		!(ft_strcmp(token->type, "dollar")))
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
