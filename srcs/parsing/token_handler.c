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

void    parse_outfile(t_infos *info)
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
				printf("bash: syntax error near unexpected token `newline`\n");
				printf("Error in handle output no outfile\n");
				return;
			}
			get_outfile(temp);
		}
		temp = temp->next;
	}
}

void    parse_infile(t_infos *info)
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
				return;
			}
			get_infile(temp);
		}
		temp = temp->next;
	}
}
