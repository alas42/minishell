#include "../../includes/minishell.h"

static void	expand_normal_dollar(t_infos *info, t_token *token, char *ret_val)
{
	ret_val = check_dollar_arg(info, token->content);
	free(token->content);
	token->content = ft_strdup(ret_val);
	free(ret_val);
	free(token->type);
	token->type = ft_strdup("literal");
}

static void	expand_lit_dollar_loop(t_infos *info, t_token *token,
	char *ret_val, char **arg)
{
	int	j;
	int	i;
	int	counter;

	i = -1;
	while (arg[++i])
	{
		counter = 0;
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '$')
			{
				ret_val = check_dollar_arg(info, arg[i]);
				token->content = merge_content(token->content, ret_val, 1);
				free(ret_val);
				counter = 1;
				break ;
			}
			j++;
		}
		if (counter == 0)
			token->content = merge_content(token->content, arg[i], 1);
	}
}

static void	expand_lit_dollar(t_infos *info, t_token *token, char *ret_val)
{
	char	**arg;
	int		i;
	int		j;
	int		counter;

	arg = ft_split(token->content, ' ');
	free(token->content);
	token->content = ft_strdup("");
	expand_lit_dollar_loop(info, token, ret_val, arg);
	free(token->type);
	token->type = ft_strdup("literal");
	free_doub_char(arg);
}

void	expand_dollar(t_infos *info)
{
	t_token	*token;
	char	*ret_val;

	token = info->tokens;
	ret_val = NULL;
	while (token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
			expand_normal_dollar(info, token, ret_val);
		else if (!(ft_strcmp(token->type, "literal_dollar")))
			expand_lit_dollar(info, token, ret_val);
		token = token->next;
	}
}
