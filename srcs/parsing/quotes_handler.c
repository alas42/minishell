#include "../includes/minishell.h"

char    *update_doubqt_content(t_token *temp)
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

void    update_doubquote_token(t_infos *info, char *from, char *to)
{
    t_token *temp;

    temp = info->tokens;
    while (temp)
    {
        if (!(ft_strcmp(temp->type, from)))
        {
            free(temp->type);
            temp->type = ft_strdup(to);
            temp->content = update_doubqt_content(temp);
            break;
        }
        temp = temp->next;
    }
}

int    check_closing_quote(t_infos *info, int pos)
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
        if (!(ft_strcmp(temp->type, "double_quote")))
        {
            close = temp->pos;
            break;
        }
        if (!(ft_strcmp(temp->type, "pipe")))
            break;
        temp = temp->next;
    }
    return (close);
}

void    remove_consec_doubqt(t_infos *info, int pos)
{
    t_token     *temp;
    int         total;
    int         i;

    temp = info->tokens;
    i = 0;
    while (i++ <= pos)
        temp = temp->next;
    while (temp)
    {
        if (!(ft_strcmp(temp->type, "double_quote")))
        {
            total = -1;
            total = ft_strlen(temp->content) % 2;
            free(temp->content);
            if (total == 1)
            {
                temp->content = ft_strdup("a");
                temp->content[0] = '"';
            }
            else
            {
                temp->content = ft_strdup(" ");
                free(temp->content);
                temp->content = ft_strdup("space");
            }
        }
        temp = temp->next;
    }
}

void    check_quotes(t_infos *info)
{
    t_token *token;
    int     close;
    int     len;

    close = -2;
    len = 0;
    token = info->tokens;

    while(token)
    {
        if (!(ft_strcmp(token->type, "double_quote")))
        {
            len = ft_strlen(token->content);
            if (len > 1)
               remove_consec_doubqt(info, token->pos);
            close = check_closing_quote(info, token->pos);
            if (close < 0)
                printf("error cannot find closing quote\n");
            else
            {
                merge_tokens(info, token->pos, close - token->pos);
                update_doubquote_token(info, "double_quote", "literal");
                token = info->tokens;
            }
        }
        token = token->next;
    }
}