#include "../inc/fdf.h"

int	get_elem_nb(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (ft_char_isdigit(*str))
		{
			i++;
			while (ft_char_isdigit(*str))
				str++;
		}
		else
			str++;
	}
	return (i);
}
