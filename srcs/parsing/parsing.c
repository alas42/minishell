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

void    handle_outfile(char *outfile, char *type, t_cmd *cmd)
{
    int i;

    i = -1;
    if (cmd->fd_outfile > 0)
    {
        i = close(cmd->fd_outfile);
        if (i < 0)
            printf("error in closing the file_des [%d] \n", cmd->fd_outfile);
        if (cmd->name_outfile != NULL)
            free(cmd->name_outfile);
    }
    if (!(ft_strcmp(type, "output_red")))
        cmd->fd_outfile = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    else
        cmd->fd_outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (cmd->fd_outfile < 0)
            printf("error in opening the file [%s] in mode [%s]\n", outfile, type);
    cmd->name_outfile = ft_strdup(outfile);
}

void    handle_infile(char *infile, char *type, t_cmd *cmd)
{
    int i;

    i = -1;
    if (cmd->fd_infile > 0)
    {
        i = close(cmd->fd_infile);
        if (i < 0)
            printf("error in closing the file_des [%d] \n", cmd->fd_infile);
    }
    cmd->fd_infile = open(infile, O_RDONLY, 0644);
    if (cmd->fd_infile < 0)
            printf("error in opening the file [%s] in mode [%s]\n", infile, type);
     if (cmd->name_infile != NULL)
        free(cmd->name_infile);
    cmd->name_infile = ft_strdup(infile);
}

void    handle_here_doc(t_token *token, t_cmd *cmd)
{
    int     i;
    char    *line;

    line = NULL;
    printf("here doc word is %s \n\n\n", token->next->content);
    (void)cmd;
    i = -1;
    while ((i = get_next_line(1, &line)) > 0)
    {
        printf("line[%s]\n", line);
        if (!(ft_strcmp(line, token->next->content)))
        {
            printf("found end \n");
            free(line);
            break;
        }
        free(line);
    }
    cmd->fd_infile = 1;
}

void	handle_redirections(t_infos *info)
{
	t_cmd	*cmd;
    t_token *red;

	cmd = info->commands;
	while(cmd)
	{
        red = cmd->redirection;
		while (red)
		{
            if (!(ft_strcmp(red->type, "output_red"))
            || !(ft_strcmp(red->type, "double_output_red")))
            {
                if (red->next != NULL && (!ft_strcmp(red->next->type, "outfile")))
                    handle_outfile(red->next->content, red->type, cmd);              
                else
                    printf("Cannot find outfile....Exiting now.. \n");
            }
            else if (!(ft_strcmp(red->type, "input_red")))
            {
                if (red->next != NULL && (!ft_strcmp(red->next->type, "infile")))
                    handle_infile(red->next->content, red->type, cmd);              
                else
                    printf("Cannot find infile....Exiting now.. \n");
            }
            else if (!(ft_strcmp(red->type, "here_doc")))
            {
                // if(red->next != NULL && (!(ft_strcmp(red->next->type, "here_doc_word")))
                cmd->fd_infile = 1;
        
                // handle_here_doc(red, cmd);
                printf("found here doc. Here doc word is [%s]\n", red->type);
            }
            red = red->next;
		}
		cmd = cmd->next;
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
    printf("--------------PRINTING ALL TOKENS AT THE END END-------------------\n\n\n\n");
    print_token_list(info->tokens);
    printf("----------------END OF TOKENS-----------------\n\n\n\n");
    move_to_cmd(info);
	handle_redirections(info);
    printf("--------------PRINTING CMDS-------------------\n\n\n\n");
    print_cmnds(info);
    printf("--------------END OF CMDS-------------------\n\n\n\n");       
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