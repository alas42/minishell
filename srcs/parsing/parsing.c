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

void    free_cmd(t_infos *info)
{
    int     i;

    i = 0;
    if (info->first_cmd == NULL)
    {
        free(info->first_cmd);
        return ;
    }
    while(info->first_cmd->arg[i] != NULL)
    {
        free(info->first_cmd->arg[i]);
        i++;
    }
    if (info->first_cmd->arg)
        free(info->first_cmd->arg);
    if(info->first_cmd->name_outfile)
        free(info->first_cmd->name_outfile);
    if (info->first_cmd->name_infile)
        free(info->first_cmd->name_infile);
    if (info->first_cmd->here_doc_eof)
        free(info->first_cmd->here_doc_eof);
    free(info->first_cmd);


}

void    start_parsing(t_infos *info)
{
    add_to_struct(info);
    if (info->tokens == NULL)
        return ;
    merge_same(info);
    check_quotes(info);
    expand_dollar(info);
    remove_space_tokens(info);
    handle_output_red(info);
    handle_input_red(info);

    printf("--------------END-------------------\n\n\n\n");
    print_token_list(info->tokens);
    printf("---------------------------------\n\n\n\n");
    move_to_cmd(info);
    //printf("--------------cmd-------------------\n\n\n\n");
    //print_cmd(info);
    //printf("---------------------------------\n\n\n\n");
}
