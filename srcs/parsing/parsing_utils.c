#include "../../includes/minishell.h"

//checks for space d = 's' digit = 'd' both = 'b'
int	ft_isspace_isdigit(char c, char d)
{
	if (d == 's')
	{
		if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r')
			return (1);
	}
	else if (d == 'd')
	{
		if (c >= 48 && c <= 57)
			return (1);
	}
	else if (d == 'b')
	{
		if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r'
			|| (c >= 48 && c <= 57))
			return (1);
	}
	return (0);
}

int	ft_isallspace(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isspace_isdigit(line[i], 's')))
			return (1);
		i++;
	}
	return (0);
}

char	*remove_space_digit(char *line, char c)
{
	if (c == 's')
	{
		while (ft_isspace_isdigit(*line, 's'))
			line++;
	}
	else if (c == 'd')
	{
		while (ft_isspace_isdigit(*line, 'd'))
			line++;
	}
	else if (c == 'b')
	{
		while (ft_isspace_isdigit(*line, 's'))
			line++;
		if (*line == '+' || *line == '-')
			line++;
		while (ft_isspace_isdigit(*line, 'd'))
			line++;
	}
	return (line);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	x;

	x = 0;
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
			n--;
		}
		else
		{
			x = *(unsigned char *)s1 - *(unsigned char *)s2;
			break ;
		}
	}
	return (x);
}

char	*char_to_str(char c, t_infos *info)
{
	char *str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
	{
		print_parsing_error(0, info);
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}
