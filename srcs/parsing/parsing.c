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

void    remove_space_tokens(t_infos *info)
{
	t_token *temp;
	int     i;

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

void	parse_here_doc(t_infos *info)
{
	t_token *token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "input_red")) && ft_strlen(token->content) == 2)
		{
			free(token->type);
			token->type = ft_strdup("here_doc");
			if (token->next && (!(ft_strcmp(token->next->type, "space"))))
				token = token->next;
			if (token->next && (!(ft_strcmp(token->next->type, "literal"))
			|| !(ft_strcmp(token->next->type, "dollar"))))
			{
				free(token->next->type);
				token->next->type = ft_strdup("here_doc_word");
			}
		}
		token = token->next;
	}
}

void    start_parsing(t_infos *info)
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


/*
	printf("--------------PRINTING CMDS-------------------\n\n\n\n");
	print_cmnds(info);
	printf("--------------END OF CMDS-------------------\n\n\n\n");
	printf("--------------PRINTING ALL TOKENS AT THE END END-------------------\n\n\n\n");
	print_token_list(info->tokens);
	printf("----------------END OF TOKENS-----------------\n\n\n\n");



*/

/*
	get_dollar(info);
	check_quotes(info);
	merge_same(info);
	get_dollar_prev(info);
	parse_here_doc(info);
	expand_dollar(info);
	merge_same(info);
	remove_space_tokens(info);
	parse_outfile(info);
	parse_infile(info);
	move_to_cmd(info);
	handle_redirections(info);


*/

/*
export one="this"

MY
<< $one cat 
hello line 1
hello line 2
this
//stops

bash
<< $one cat 
hello line 1
hello line 2
$one
//stops

// echo "$" should we print $

ECHO CASES TO HANDLE
echo $123
	my 	- []
	bash - [23]

echo $USER$12USER$USER=4$USER12
	my 		- yassharmyassharm=4
	bash	- yassharm2USERyassharm=4

echo $USER $USER9999 $USER8888 $USER7777 "$USER"
	my [yassharm    yassharm]
	bash [yassharm yassharm]

CD CASES TO HANDLE

cd ''
	my - [cd "space"]
	bash - [cd]

*/