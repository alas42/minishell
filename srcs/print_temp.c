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
