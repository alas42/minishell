#include "../includes/minishell.h"

int	closing_quote_helper(t_token *temp, int mode)
{
	int	close;

	close = -1;
	if (mode == 2)
	{
		if (!(ft_strcmp(temp->type, "double_quote")))
			close = temp->pos;
	}
	if (mode == 1)
	{
		if (!(ft_strcmp(temp->type, "single_quote")))
			close = temp->pos;
	}
	return (close);
}

int	check_closing_quote(t_infos *info, int pos, int mode)
{
	t_token	*temp;
	int		i;
	int		close;

	i = 0;
	close = -1;
	temp = info->tokens;
	while (i++ <= pos)
		temp = temp->next;
	while (temp)
	{
		close = closing_quote_helper(temp, mode);
		if (close >= 0)
			break ;
		temp = temp->next;
	}
	return (close);
}

int	handle_double_quote(t_token *token, t_infos *info)
{
	int	close;

	close = -2;
	close = check_closing_quote(info, token->pos, 2);
	if (close < 0)
	{
		print_parsing_error(2, info);
		return (0);
	}
	else
	{
		merge_tokens(info, token->pos, close - token->pos);
		update_token_type(info, "double_quote", "literal");
		return (1);
	}
}

int	handle_single_quote(t_token *token, t_infos *info)
{
	int	close;

	close = -2;
	close = check_closing_quote(info, token->pos, 1);
	if (close < 0)
	{
		print_parsing_error(1, info);
		return (0);
	}
	else
	{
		merge_tokens(info, token->pos, close - token->pos);
		update_token_type(info, "single_quote", "literal");
		return (1);
	}
}

void	check_quotes(t_infos *info)
{
	t_token	*token;
	int		ret;

	ret = -1;
	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "double_quote")))
		{
			ret = handle_double_quote(token, info);
			if (ret == 1)
				token = info->tokens;
		}
		else if (!(ft_strcmp(token->type, "single_quote")))
		{
			ret = handle_single_quote(token, info);
			if (ret == 1)
				token = info->tokens;
		}
		ret = -1;
		token = token->next;
	}
}
