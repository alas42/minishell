/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:28:28 by avogt             #+#    #+#             */
/*   Updated: 2021/10/31 13:56:30 by yassharm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

void	print_double_char(char **arg)
{
	int		i;

	i = 0;
	while(arg[i])
	{
		printf("arg[%d] - [%s]\n", i, arg[i]);
		i++;
	}
}

void	print_cmnd_single(t_cmd *cmd)
{
	int		i;
	t_token	*red;

	i  = 0;
	if (cmd == NULL)
	{
		printf("found a null command in temp print\n");
		return;
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
	printf("\nredirections are as follow --\n\n");
	while(red)
	{
		printf("pos[%d] content[%s] \t\ttype[%s]\n",red->pos, red->content, red->type);
		red = red->next;
	}
	printf("\n\ninput_fd [%d] output_fd [%d]\n", cmd->fd_infile, cmd->fd_outfile);
	if (cmd->name_outfile)
		printf("outfile_fd file [%s]\n",  cmd->name_outfile);
	if (cmd->name_infile)
		printf("infile_fd file [%s]\n", cmd->name_infile);
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

void	remove_last_space_tokens(t_token *temp)
{
	if (temp && !(ft_strncmp(temp->type, "space", 5)))
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
		free(temp->content);
		free(temp->type);
		free(temp);
	}
}

void	remove_space_tokens(t_infos *info)
{
	t_token	*temp;
	int		i;

	temp = info->tokens;
	i = 0;
	if (temp != NULL && temp->next == NULL)
	{
		if (!(ft_strncmp(temp->type, "space", 5)))
		{
			free(temp->content);
			free(temp->type);
			free(temp);
			info->tokens = NULL;
		}
		return ;
	}
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
	remove_last_space_tokens(temp);
}

void	check_pipe_error(t_infos *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "pipe")))
		{
			if (ft_strlen(token->content) > 1 || token->pos == 0
				|| token->next == NULL)
				print_pipe_error(1, info);
			if (token->next && !(ft_strcmp(token->next->type, "pipe")))
				print_pipe_error(1, info);
		}
		token = token->next;
	}
}


void	check_only_dollar(t_infos *info)
{
	t_token  *token;

	token = info->tokens;
	while(token)
	{
		if (!(ft_strcmp(token->type, "dollar")))
		{
			if (ft_strlen(token->content) == 1)
			{
				free(token->type);
				token->type = ft_strdup("literal");
			}
		}
		token = token->next;
	}
}

void	check_dollar_type(t_infos *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "literal_space")))
		{
			if (ft_strlen(token->content) == 0)
			{
				free(token->type);
				token->type = ft_strdup("space");
			}
			else
			{
				free(token->type);
				token->type = ft_strdup("literal");
			}
		}
		token = token->next;
	}
}

void	check_empty_literal(t_infos *info)
{
	t_token  *token;

	token = info->tokens;
	while(token)
	{
		if (!(ft_strcmp(token->type, "literal")))
		{
			if (ft_strlen(token->content) == 0)
			{
				free(token->content);
				token->content = ft_strdup(" ");
			}
		}
		token = token->next;
	}
}

void	start_parsing(t_infos *info)
{
	add_to_struct(info);
	if (info->tokens == NULL)
		return ;
	get_dollar(info);
	check_quotes(info);


	//printf("--------------00Printing the tokens before expansion-----------\n");
	//print_token_list(info->tokens);
	//printf("--------------End--------------------\n");

	check_only_dollar(info);
	expand_dollar(info);
	check_dollar_type(info);



	merge_same(info);
	//printf("--------------01Printing the tokens after expansion-----------\n");
	//print_token_list(info->tokens);
	//printf("--------------End--------------------\n");
	remove_space_tokens(info);
	if (info->tokens == NULL)
		return;
	parse_outfile(info);
	parse_infile(info);
	check_pipe_error(info);
	remove_space_tokens(info);
	//check_empty_literal(info);
	//printf("--------------Printing the tokens after expansion-----------\n");
	//print_token_list(info->tokens);
	//printf("--------------End--------------------\n");


	if (info->tokens == NULL)
		return;
	move_to_cmd(info);
	handle_redirections(info);
}
