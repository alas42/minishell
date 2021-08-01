#include "../includes/libft.h"

static void	add_to_i(size_t *i, char c, int protection)
{
	if (protection == 1)
	{
		if (c == '-')
			*i = *i + 1;
	}
	else if (protection == 2)
	{
		if (c == '.')
			*i = *i + 1;
	}
}

static void	change_sign(int *sign, char c)
{
	if (c == '-')
		*sign = -1;
	else
		*sign = 1;
}

float	ft_atof(const char *str, size_t *i)
{
	float	num;
	float	dec;
	float	tmp;
	int		sign;

	num = 0.0;
	sign = 1;
	dec = 0.0;
	tmp = 1.0;
	while (ft_isspace(str[(*i)]))
		*i = *i + 1;
	change_sign(&sign, str[*i]);
	add_to_i(i, str[*i], 1);
	while (str[*i] && ft_isdigit(str[*i]) && str[*i] != '.')
	{
		num = (num * 10) + (str[*i] - '0');
		*i = *i + 1;
	}
	add_to_i(i, str[*i], 2);
	while (str[*i] && ft_isdigit(str[*i]))
	{
		tmp *= 0.1;
		dec += (tmp * (str[(*i)++] - '0'));
	}
	return ((dec + num) * sign);
}
