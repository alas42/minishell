#include "../includes/minishell.h"

void    upfate_tokens(t_infos *info)
{
    t_token *temp;

    //print_token_list(info->tokens);
    temp = info->tokens;
    while (temp)
    {
        printf("token type [%s], token [%s]\n", temp->type, temp->content);
        temp = temp->next;
    }
}

void    start_parsing(t_infos *info)
{
    add_to_struct(info);
    merge_same(info);
    upfate_tokens(info);
    free_tokens(info);
}
