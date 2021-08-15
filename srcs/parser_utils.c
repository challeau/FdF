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

void	check_max_width(int *width, char *line)
{
	int	buff;

	buff = get_elem_nb(line);
	if (buff > *width)
		*width = buff;
}

void	check_for_dents(char **data, __attribute__((unused))t_vec3f ***map)
{
	int i;
	int j;
	int buff;
	int width;

	i = 0;
	width = get_elem_nb(data[i]);
	while (data[i] && *data[i] != '\0')
	{
		j = 0;
		buff = get_elem_nb(data[i]);
		while (buff + j< width)
		{
			map[0][i][buff + j] = map[0][i][buff - 1];
			j++;
		}
		i++;
	}
}
