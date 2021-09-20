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

void    handle_outfile(char *outfile, char *type, t_cmnd *cmd)
{
    int i;

    i = -1;
    if (cmd->output_fd > 0)
    {
        printf("closing outfile[%s] fd [%d] mode [%s]\n", cmd->name_outfile, cmd->output_fd, type);
        i = close(cmd->output_fd);
        if (i < 0)
            printf("error in closing the file_des [%d] \n", cmd->output_fd);
        if (cmd->name_outfile != NULL)
            free(cmd->name_outfile);
    }
    if (!(ft_strcmp(type, "output_red")))
        cmd->output_fd = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);   
    else
        cmd->output_fd = open(outfile, O_TRUNC | O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->output_fd < 0)
            printf("error in opening the file [%s] in mode [%s]\n", outfile, type);
    cmd->name_outfile = ft_strdup(outfile);
}

void    handle_infile(char *infile, char *type, t_cmnd *cmd)
{
    int i;

    i = -1;
    if (cmd->input_fd > 0)
    {
        printf("closing infile[%s] fd [%d] mode [%s]\n", cmd->name_infile, cmd->input_fd, type);
        i = close(cmd->input_fd);
        if (i < 0)
            printf("error in closing the file_des [%d] \n", cmd->input_fd);
    }
    cmd->input_fd = open(infile, O_RDONLY, 0644);
    if (cmd->input_fd < 0)
            printf("error in opening the file [%s] in mode [%s]\n", infile, type);
     if (cmd->name_infile != NULL)
        free(cmd->name_infile);
    cmd->name_infile = ft_strdup(infile);
}

void	handle_redirections(t_infos *info)
{
	t_cmnd	*cmd;
    t_token *red;


	cmd = info->commands;
	while(cmd)
	{
        red = cmd->redirection;
        printf("------------------------\n");
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
	handle_redirections(info);
                printf("--------------PRINTING CMDS-------------------\n\n\n\n");
                print_cmnds(info);
                printf("--------------END OF CMDS-------------------\n\n\n\n");
}

/*
    echo "hello world" >> a >> b < a >>papa | grep all >> al > la
    ls -ll | grep all >> a | << a cat *
    ls -ll > a > v | grep appd | <a <v >caa | cat all |
*/

/*
Things to do

5. Need to do proper expansions after cmnds are build (inside exec)
6. Need to execute the redirections;

*/
