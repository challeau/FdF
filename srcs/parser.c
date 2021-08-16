#include "../inc/fdf.h"

/* static void	z_scale(t_vec3f **map, t_data data) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	while (i < data.map_len) */
/* 	{ */
/* 		map[0][i].z += -data.min_z; */
/* 		i++; */
/* 	} */
/* } */

/* static void	get_z_limits(t_vec3f *map, t_data *data) */
/* { */
/* 	int	i; */
/* 	int	max_buff; */
/* 	int	min_buff; */

/* 	i = 0; */
/* 	max_buff = map[0].z; */
/* 	min_buff = map[0].z; */
/* 	while (i < data->map_len) */
/* 	{ */
/* 		if (map[i].z > max_buff) */
/* 			max_buff = map[i].z; */
/* 		if (map[i].z < min_buff) */
/* 			min_buff = map[i].z; */
/* 		i++; */
/* 	} */
/* 	data->max_z = max_buff; */
/* 	data->min_z = min_buff; */
/* 	if (min_buff < 0) */
/* 		z_scale(&map, *data); */
/* 	data->min_z = 0; */
/* } */

static t_vec3f	*assign_map(t_data *data, char **file_content)
{
	int		i;
	int		j;
	char	**tmp;
	t_vec3f	*map = (t_vec3f *)malloc((data->map_height * data->map_width + 1) * sizeof(t_vec3f));

	i = 0;
	while (file_content[i] && *file_content[i] != '\0')
	{
		j = 0;
		tmp = ft_split(file_content[i], ' ');
		while (tmp[j] && *tmp[j] != '\0')
		{
			map[j + (i * data->map_width)].x = j
				* 20 - data->map_width * 10;
			map[j + (i * data->map_width)].y = i
				* 20 - data->map_height * 10;
			map[j + (i * data->map_width)].z = ft_atoi(tmp[j])
				* 2.5;
			j++;
		}
		ft_memdel_strptr(tmp);
		i++;
	}
//	check_for_dents(file_content, &data->map);
	ft_memdel_strptr(file_content);
	return (map);
}

static char	**get_file_contents(int fd, int *width, int *height)
{
	int		i;
	int		ret;
	char	*line;
	char	**content;

	i = 0;
	ret = get_next_line(fd, &line);
	content = (char **)malloc(1000 * sizeof(char *));
	while (ret >= 0 && i < 999)
	{
		if (*line != '\0')
		{
			check_max_width(width, line);
			*height += 1;
			content[i++] = ft_strdup(line);
			content[i] = NULL;
		}
		ft_memdel(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		error("couldn't open your file.");
	return (content);
}

void	get_data(char *source_file, t_data *data)
{
	int		fd;
	int		width;
	int		height;
	char	**file_content;

	fd = open(source_file, O_RDONLY);
	height = 0;
	width = 0;
	file_content = get_file_contents(fd, &width, &height);
	close(fd);
	data->map_width = width;
	data->map_height = height;
	data->map_len = height * width;
	data->map = assign_map(data, file_content);

//	get_z_limits(map, data);
}
