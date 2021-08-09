#include "../../includes/minishell.h"

void    unname_function(t_infos *info)
{
    print_token_list(info->tokens);
}

void    start_parsing(t_infos *info)
{
    add_to_struct(info);
    merge_same(info);
    unname_function(info);
    free_tokens(info);
}