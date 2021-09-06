#include "../includes/minishell.h"

//fill the info->tokens->type by cmp character to defined token type
void    get_token_type(t_token *new, t_infos *info, int i)
{
    // printf("gettokentype i is [%d]\n", i);
    if (info->line[i] == '|')
        new->type = ft_strdup("pipe");
    else if (info->line[i] == '<')
        new->type = ft_strdup("input_red");
    else if (info->line[i] == '>')
        new->type = ft_strdup("output_red");
    else if (info->line[i] == 39)
        new->type = ft_strdup("single_quote");
    else if (info->line[i] == 34)
        new->type = ft_strdup("double_quote");
    else if (info->line[i] == '$')
        new->type = ft_strdup("dollar");
    else if (info->line[i] == '?')
        new->type = ft_strdup("question");
    else if (ft_isspace_isdigit(info->line[i], 's'))
        new->type = ft_strdup("space");
    else
        new->type = ft_strdup("literal");
}

//initialize an empty instance of t_token struct
t_token  *token_init()
{
    t_token  *data;

    data = (t_token *)malloc(sizeof(t_token));
    if (data == NULL)
        return (NULL);
    data->content = NULL;
    data->type = NULL;
    data->pos = -1;
    data->next = NULL;
    data->prev = NULL;
    return (data);
}

//adds the t_token instance in info->tokens link list
void    lst_add_back(t_infos *info, t_token *new)
{
	t_token	*ls;
	if (new == NULL)
		return ;
	if (info->tokens)
		ls = info->tokens;
	else
	{
		info->tokens = new;
		return ;
	}
	while (ls->next != NULL)
		ls = ls->next;
	new->prev = ls;
	ls->next = new;
}

//returns the last element of t_token slinklist
t_token	*ft_lstlast_token(t_token *lst)
{
	t_token	*p;

	p = lst;
	if (lst == NULL)
		return (NULL);
	while (p->next != NULL)
		p = p->next;
	return (p);
}

//step1
//add node of token linklist splitting the initial received line. everychracter of line is a node in info->token linklist
void    add_to_struct(t_infos *info)
{
    int     i;
    t_token *new;

    i = 0;
    while (info->line[i] != '\0')
    {
        new = token_init();
        if (new == NULL)
            printf("ERROR in add struct\n");
        new->content = char_to_str(info->line[i]);
        new->pos = i;
        get_token_type(new, info, i);
        lst_add_back(info, new);
        i++;
    }
}
