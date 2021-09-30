#include "../includes/minishell.h"

//----------------------------------------------------------------//


//temp function to print the stuc t_info data
// echo "hello world" 'this' | wc -l ; ls -l | grep *

void	print_token_list(t_token *tokens)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = tokens;
	if (temp == NULL)
		return;
	while(temp)
	{
		if (i < 10)
			printf("pos [%d]\t\tchar [%s]\t [%s]\n", temp->pos, temp->content, temp->type);
		else
			printf("pos [%d]\tchar [%s]\t [%s]\n", temp->pos, temp->content, temp->type);
		i++;
		temp = temp->next;
	}
}

void	print_info(t_infos *info)
{
	int		i;
	t_token	*token;

	 i = 0;
	printf("printing tokens\n\n\n");
	token = info->tokens;
	while (token)
	{
		if (i < 10)
			printf("pos [%d]\t\tchar [%s]\t [%s]\n", token->pos, token->content, token->type);
		else
			printf("pos [%d]\tchar [%s]\t [%s]\n", token->pos, token->content, token->type);
		token = token->next;
		i++;
	}
	// printf("info->line [%s]\n", info->line);
	// printf("info pos_path - [%d]\n", info->pos_path);
	// while (info->paths[i] != 0)
	// {
	//     printf("[%d] - [%s]\n",i,  info->paths[i]);
	//     i++;
	// }
	// printf("info->fd[0] - [%d]\n fd[1] - [%d]\n", info->pipe[0], info->pipe[1]);
}

void	print_cmnd_single(t_cmd *cmd)
{
	int		i;
	t_token	*red;

	i  = 0;
	if (cmd == NULL)
	{
		printf("found a null command in temp print\n");
	}
	printf("INDEX 		[%d]\n", cmd->index);
	printf("BUILTINS 	[%d]\n", cmd->builtin);
	printf("PIPEIN		[%d]\n", cmd->pipe_in);
	printf("PIPEOUT		[%d]\n", cmd->pipe_out);
	if (cmd->arg != NULL)
	{
		while(cmd->arg[i] != NULL)
		{
			printf("ARG[%d] [%s]\n", i, cmd->arg[i]);
			i++;
		}
	}
	red = cmd->redirection;
	// printf("\nredirections are as follow --\n");
	while(red)
	{
		// printf("content[%s] type[%s]\n", red->content, red->type);
		red = red->next;
	}
	if (cmd->name_outfile)
		printf("outfile_fd is	[%d] for file [%s]\n", cmd->fd_outfile, cmd->name_outfile);
	if (cmd->name_infile)
		printf("infile_fd is 	[%d] for file [%s]\n", cmd->fd_infile, cmd->name_infile);
}

void	print_cmnds(t_infos *info)
{
	t_cmd	*commands;

	commands = info->commands;
	if (commands == NULL)
		return;
	while (commands)
	{

		printf("\n------------------00---------------------\n");
		print_cmnd_single(commands);
		commands = commands->next;
	}
}

