#include "../includes/minishell.h"

t_cmd    *cmd_init()
{
    t_cmd   *new;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (new == NULL)
        return (NULL);
    new->arg = NULL;
    new->index = -1;
    new->process = -1;
    new->fd_infile = -1;
    new->fd_outfile = -1;
    new->here_doc_in = -1;
    new->builtin = -1;
    new->pipe_in = -1;
    new->pipe_out = -1;
    new->in_red = -1;
    new->out_red = -1;
    new->name_infile = NULL;
    new->name_outfile = NULL;
    new->here_doc_eof = NULL;
    new->next = NULL;
    new->prec = NULL;
    return (new);
}

char    *merge_content(char *str, char *content)
{
    char *temp;

    temp = str;
    str = ft_strjoin(temp, content);
    free(temp);
    temp = str;
    str = ft_strjoin(temp, " ");
    free(temp);
    return (str);
}

void    print_cmd(t_infos *info)
{
    t_cmd   *new;
    int     i;

    new = info->first_cmd;
    if (new == NULL)
    {
        printf("NULL in print_cmd\n");
        return ;
    }
    printf("new->args are ------ \n");
    i = 0;
    while(new->arg[i])
    {
        printf("ARG[%d] [%s]\n", i, new->arg[i]);
        i++;
    }
    printf("-------------------------\n");
    printf("index - [%d]\n", new->index);
    printf("builtin - [%d]\n", new->builtin);
    printf("pipe_in - [%d]\n", new->pipe_in);
    printf("pipe_out - [%d]\n", new->pipe_out);
    printf("fd_outfile - [%d]\n", new->fd_outfile);
    printf("fd_infile - [%d]\n", new->fd_infile);
    printf("in_red - [%d]\n", new->in_red);
    printf("out_red - [%d]\n", new->out_red);
    printf("here_doc_in - [%d]\n", new->here_doc_in);
    printf("here_doc_eof - [%s]\n", new->here_doc_eof);
    printf("name_infile - [%s]\n", new->name_infile);
    printf("name_outfile - [%s]\n", new->name_outfile);
   
}

void    add_to_cmd(t_infos *info)
{
    t_cmd   *new;
    t_token *token;
    char    *str;

    str = NULL;
    token = info->tokens;
    new = cmd_init();
    if (new == NULL)
        printf("error in add to cmd 01\n");
    while (token)
    {
        if (!(ft_strcmp(token->type, "pipe")))
            break;
        // if (!(ft_strcmp(token->type, "literal")))
        str = merge_content(str, token->content);
        if (!(ft_strcmp(token->type, "here_doc")))
            new->here_doc_in = 1;
        if (!(ft_strcmp(token->type, "here_doc_word")))
            new->here_doc_eof = ft_strdup(token->content);
        if (!(ft_strcmp(token->type, "input_red")))
            new->in_red = 1;
        if (!(ft_strcmp(token->type, "infile")))
            new->name_infile = ft_strdup(token->content);
        if (!(ft_strcmp(token->type, "output_red")))
            new->out_red = 1;
        if (!(ft_strcmp(token->type, "double_output_red")))
            new->out_red = 2;
        if (!(ft_strcmp(token->type, "outfile")))
            new->name_outfile = ft_strdup(token->content);
        token = token->next;
    }
    new->arg = ft_split_char(str, ' ');
    free(str);
    info->first_cmd = new;
    if(token)
        printf("token type in the end [%s]\n", token->type);
    else
        printf("end of token \n");
}


