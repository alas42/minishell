#include "../includes/minishell.h"

void    remove_space_tokens(t_infos *info)
{
    t_token *temp;
    int     i;

    // print_token_list(info->tokens);
    // printf("-----------/------------------------------\n");
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

    if (temp && !(ft_strncmp(temp->type, "space", 5)))
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
        free(temp->content);
        free(temp->type);
        free(temp);
    }
    // print_token_list(info->tokens);

}

void    update_tokens_type(t_infos *info)
{
    t_token *temp;

    temp = info->tokens;
    while (temp)
    {
        if (!(ft_strcmp(temp->type, "pipe")))
        {
            if (ft_strlen(temp->content) != 1)
                printf("error invalide character after pipe\n");
        }
        if (!(ft_strcmp(temp->type, "input_red")))
        {
            if (ft_strlen(temp->content) > 2)
                printf("error - invalid character after >>\n");
            if (ft_strlen(temp->content)== 2)
            {
                free(temp->type);
                temp->type = ft_strdup("here_doc");
            }
        }
       temp = temp->next;  
    }
}

void    start_parsing(t_infos *info)
{
    add_to_struct(info);
    // print_token_list(info->tokens);
    printf("---------------------------------\n\n\n\n");
    if (info->tokens == NULL)
        return ;
    merge_same(info);
    expand_dollar(info);
    remove_space_tokens(info);
    handle_output_red(info);
    handle_input_red(info);
    print_token_list(info->tokens);
    free_tokens(info);

}
