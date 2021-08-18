#include "../includes/minishell.h"

void    get_outfile(t_token *temp)
{
    if (ft_strcmp(temp->next->type, "literal"))
    {
        printf("Unexpected token near output red\n");
        printf("get_output_file file name missing\n");
    }
    else
    {
        free(temp->next->type);
        temp->next->type = ft_strdup("outfile");
    }
}

void    get_infile(t_token *temp)
{
    if (ft_strcmp(temp->next->type, "literal"))
    {
        printf("Unexpected token near output red\n");
        printf("get_input_file file name or here_doc word missing\n");
    }
    else
    {
        free(temp->next->type);
        if (ft_strlen(temp->content) == 1)
            temp->next->type = ft_strdup("infile");
        else
            temp->next->type = ft_strdup("here_doc_word");
    }
}

void    handle_output_red(t_infos *info)
{
    t_token *temp;

    temp = info->tokens;
    while (temp)
    {
       if (!(ft_strcmp(temp->type, "output_red")))
        {          
            if (ft_strlen(temp->content) > 2)
                printf("error - invalid character after >>\n");
            else if (ft_strlen(temp->content)== 2)
            {
                free(temp->type);
                temp->type = ft_strdup("double_output_red");
            }
            if (temp->next == NULL)
            {
                printf("bash: syntax error near unexpected token `newline'");
                printf("Error in hanfle output no outfile\n");
                return;
            }
            get_outfile(temp);
        }
        temp = temp->next;
    }
}

void    handle_input_red(t_infos *info)
{
    t_token *temp;

    temp = info->tokens;
    while (temp)
    {
        if (!(ft_strcmp(temp->type, "input_red")))
        {
            if (ft_strlen(temp->content) > 2)
                printf("error - invalid character after << ");
            else if (ft_strlen(temp->content) == 2)
            {
                free(temp->type);
                temp->type = ft_strdup("here_doc");
            }
             if (temp->next == NULL)
            {
                printf("bash: syntax error near unexpected token `newline'");
                printf("Error in hanfle output no outfile\n");
                return;
            }
            get_infile(temp);
        }
        temp = temp->next;
    }
}
//echo "hello $world" 'this $ $,m' | wc -l | ls -l | << grep 'a' >> outfile

void    update_dollar_type(t_infos *info, int pos)
{
    t_token *temp;
    int     i;

    i = 0;
    temp = info->tokens;
    while (i < pos)
    {
        temp = temp->next;
        i++;
    }
    free(temp->type);
    temp->type = ft_strdup("dollar");
}

void    expand_dollar(t_infos *info)
{
    t_token *temp;
    int     i;

    i = 0;
    temp = info->tokens;
    while (temp && (ft_strcmp(temp->type, "pipe")))
    {
        if (ft_strcmp(temp->type, "dollar") == 0)
        {
            if (temp->next != NULL && !(ft_strcmp(temp->next->type, "literal")))
            {
                merge_tokens(info, i, 1);
                update_dollar_type(info, i);
                temp = info->tokens;
                i = 0;
            }
        }
        i++;
        temp = temp->next;
    }
}