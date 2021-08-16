#include "../inc/fdf.h"

void	z_scale(t_vec3f **map, t_data data)
{
	int	i;

	i = 0;
	while (i < data.map_len)
	{
		map[0][i].z += -data.min_z;
		i++;
	}
}

void	get_z_limits(t_vec3f *map, t_data *data)
{
	int	i;
	int	max_buff;
	int	min_buff;

	i = 0;
	max_buff = map[0].z;
	min_buff = map[0].z;
	while (i < data->map_len)
	{
		if (map[i].z > max_buff)
			max_buff = map[i].z;
		if (map[i].z < min_buff)
			min_buff = map[i].z;
		i++;
	}
	data->max_z = max_buff;
	data->min_z = min_buff;
	if (min_buff < 0)
		z_scale(&map, *data);
	data->min_z = 0;
}

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

void	check_dimensions(int *width, int *height, char *line)
{
	int	buff;

	buff = get_elem_nb(line);
	if (buff > *width)
		*width = buff;
	*height += 1;
}
