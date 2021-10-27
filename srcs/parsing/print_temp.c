#include "../includes/minishell.h"

/*
** temp function to print the stuc t_info data
** echo "hello world" 'this' | wc -l ; ls -l | grep *
*/
void	print_token_list(t_token *tokens)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = tokens;
	if (temp == NULL)
		return ;
	while (temp)
	{
		if (i < 10)
		{
			printf("pos [%d]\t\tchar [%s]\t [%s]\n",
				temp->pos, temp->content, temp->type);
		}
		else
		{
			printf("pos [%d]\tchar [%s]\t [%s]\n",
				temp->pos, temp->content, temp->type);
		}
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
		{
			printf("pos [%d]\t\tchar [%s]\t [%s]\n",
				token->pos, token->content, token->type);
		}
		else
		{
			printf("pos [%d]\tchar [%s]\t [%s]\n",
				token->pos, token->content, token->type);
		}
		token = token->next;
		i++;
	}
}

static void	print_cmnd_single_2(t_cmd *cmd, t_token *red)
{
	printf("\nredirections are as follow --\n\n");
	while (red)
	{
		printf("pos[%d] content[%s] \t\ttype[%s]\n",
			red->pos, red->content, red->type);
		red = red->next;
	}
	printf("\n\ninput_fd [%d] output_fd [%d]\n",
		cmd->fd_infile, cmd->fd_outfile);
	if (cmd->name_outfile)
		printf("outfile_fd file [%s]\n", cmd->name_outfile);
	if (cmd->name_infile)
		printf("infile_fd file [%s]\n", cmd->name_infile);
}

void	print_cmnd_single(t_cmd *cmd)
{
	int		i;
	t_token	*red;

	i = 0;
	if (cmd == NULL)
	{
		printf("found a null command in temp print\n");
		return ;
	}
	printf("INDEX 		[%d]\n", cmd->index);
	printf("BUILTINS 	[%d]\n", cmd->builtin);
	printf("PIPEIN		[%d]\n", cmd->pipe_in);
	printf("PIPEOUT		[%d]\n", cmd->pipe_out);
	if (cmd->arg != NULL)
	{
		while (cmd->arg[i] != NULL)
		{
			printf("ARG[%d] [%s]\n", i, cmd->arg[i]);
			i++;
		}
	}
	red = cmd->redirection;
	print_cmnd_single_2(cmd, red);
}

void	print_cmnds(t_infos *info)
{
	t_cmd	*commands;

	commands = info->commands;
	if (commands == NULL)
		return ;
	while (commands)
	{
		printf("\n------------------00---------------------\n");
		print_cmnd_single(commands);
		commands = commands->next;
	}
}
