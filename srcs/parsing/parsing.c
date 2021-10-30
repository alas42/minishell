#include "../includes/minishell.h"

void	remove_last_space_tokens(t_token *temp)
{
	if (temp && !(ft_strncmp(temp->type, "space", 5)))
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
		free(temp->content);
		free(temp->type);
		free(temp);
	}
}

void	remove_space_tokens(t_infos *info)
{
	t_token	*temp;
	int		i;

	temp = info->tokens;
	i = 0;
	if (temp->next == NULL)
		return ;
	while (temp && temp->next)
	{
		if (!(ft_strncmp(temp->type, "space", 5)))
		{
			merge_tokens(info, i, 1);
			temp = info->tokens;
			i = 0;
		}
		temp = temp->next;
		i++;
	}
	remove_last_space_tokens(temp);
}

void	start_parsing(t_infos *info)
{
	add_to_struct(info);
	if (info->tokens == NULL)
		return ;
	get_dollar(info);
	check_quotes(info);
	expand_dollar(info);
	merge_same(info);
	remove_space_tokens(info);
	parse_outfile(info);
	parse_infile(info);
	move_to_cmd(info);
	handle_redirections(info);
}
