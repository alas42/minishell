#include "../includes/libft.h"

int	ft_isalpha(int c)
{
	int	char_c;

	char_c = c;
	if (char_c > 64 && char_c < 91)
		return (1);
	else if (char_c > 96 && char_c < 123)
		return (1);
	return (0);
}
