#include "../includes/minishell.h"

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
    if (temp && !(ft_strncmp(temp->type, "space", 5)))
    {
        temp->prev->next = NULL;
        temp->prev = NULL;
        free(temp->content);
        free(temp->type);
        free(temp);
    }
}

void    start_parsing(t_infos *info)
{
    add_to_struct(info);
    if (info->tokens == NULL)
        return ;
    get_dollar(info);   
    check_quotes(info);
    merge_same(info);   
    get_dollar_prev(info);
    remove_space_tokens(info);
    handle_output_red(info);
    handle_input_red(info);
    expand_dollar(info);
    move_to_cmd(info);
	handle_redirections(info);
}

/*
    echo "echo""this""is"'a''test'"wow's"
    echo "hello world" >> a >> b < a >>papa | grep all >> al > la
    ls -ll | grep all >> a | << a cat *
    ls -ll > a > v | grep appd | <a <v >caa | cat all |
*/

/*
    printf("--------------PRINTING CMDS-------------------\n\n\n\n");
    print_cmnds(info);
    printf("--------------END OF CMDS-------------------\n\n\n\n");
    printf("--------------PRINTING ALL TOKENS AT THE END END-------------------\n\n\n\n");
    print_token_list(info->tokens);
    printf("----------------END OF TOKENS-----------------\n\n\n\n");   

*/