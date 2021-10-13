#include "../includes/minishell.h"

//Remove the first and last char from content '' ""
char    *update_quotes_content(t_token *temp)
{
    char    *str;
    int     len;
    int     i;
    i = 0;

    len = ft_strlen(temp->content);
    str = (char *)malloc(sizeof(char) * len);
    while(i < len - 2)
    {
        str[i] = temp->content[i+1];
        i++;
    }
    str[i] = '\0';
    free(temp->content);
    return(str);
}


int     check_dollar(char *content)
{
    int     i;
    int     len;

    i = 0;
    len = ft_strlen(content);
    while (i < len)
    {
        if (content[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

//Update the type of token
void    update_token_type(t_infos *info, char *from, char *to)
{
    t_token *temp;
    int     i;

    i = -1;
    temp = info->tokens;
    while (temp)
    {
        if (!(ft_strcmp(temp->type, from)))
        {
            if (!(ft_strcmp(temp->type, "double_quote")))
                i = check_dollar(temp->content);
            free(temp->type);
            if (i != 1)
                temp->type = ft_strdup(to);
            else
                temp->type = ft_strdup("literal_dollar");
            temp->content = update_quotes_content(temp);
            break;
        }
        temp = temp->next;
    }
}

int    check_closing_quote(t_infos *info, int pos, int mode)
{
    t_token *temp;
    int     i;
    int     close;

    i = 0;
    close = -1;
    temp = info->tokens;
    while (i++ <= pos)
        temp = temp->next;
    while (temp)
    {
        if (mode == 2)
        {
            if (!(ft_strcmp(temp->type, "double_quote")))
            {
                close = temp->pos;
                break;
            }
        }
        if (mode == 1)
        {
            if (!(ft_strcmp(temp->type, "single_quote")))
            {
                close = temp->pos;
                break;
            }
        }
        if (!(ft_strcmp(temp->type, "pipe")))
            break;
        temp = temp->next;
    }
    return (close);
}

//echo "$hello" '$hello' $hello
//Need to do something about the errors and handling their return code
void    check_quotes(t_infos *info)
{
    t_token *token;
    int     close;

    close = -2;
    token = info->tokens;
  
    while(token)
    {
        if (!(ft_strcmp(token->type, "double_quote")))
        {
            close = check_closing_quote(info, token->pos, 2);
            if (close < 0)
                printf("error cannot find closing quote\n");
            else
            {
                merge_tokens(info, token->pos, close - token->pos);
                update_token_type(info, "double_quote", "literal");
                token = info->tokens;
            }
            close = -2;
        }
        else if (!(ft_strcmp(token->type, "single_quote")))
        {
            close = check_closing_quote(info, token->pos, 1);
            if (close < 0)
                printf("error cannot find closing quote\n");
            else
            {
                merge_tokens(info, token->pos, close - token->pos);
                update_token_type(info, "single_quote", "literal");
                token = info->tokens;
            }
        }
        close = -2;
            token = token->next;
    }
}