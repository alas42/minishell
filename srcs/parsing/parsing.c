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

void	handle_redirections(t_infos *info)
{
	t_cmnd	*cmd;
    t_token *temp_token;

	printf("\n\ninside redirection handler\n");
	cmd = info->commands;
	while(cmd)
	{
        temp_token = cmd->redirection;
        printf("------------------------\n");
		while (temp_token)
		{
			printf("content [%s] \n", temp_token->content);
            temp_token = temp_token->next;
		}
        printf("------------------------\n");
		cmd = cmd->next;
	}
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
	printf("--------------PRINTING CMDS-------------------\n\n\n\n");
    print_cmnds(info);
	printf("--------------END OF CMDS-------------------\n\n\n\n");
	// handle_redirections(info);
}

/*
ls -ll | grep all >> a | << a cat *
ls -ll > a > v | grep appd | <<a <<v <<c | cat all |
    THINGS TO FREE

    CMND - redirections
                - content
                - type
                - redirection node

         - Double_args
        -cmnd node
*/

/*
Things to do

1. Last command in move_to_cmnd not working
2. Need to free every command
    - Need ft_lstlast for cmd
    - Need to structure the file properly
3. I need to update the commands->redirection type and content
    - Need to remove pipe from redirection
4. Need to mege old code from laptop for single and double quotes;
5. Need to do proper expansions after cmnds are build (inside exec)
6. Need to execute the redirections;

*/
