#include "../inc/fdf.h"

static void	z_scale(t_vec3f ***map, t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i])
	{
		j = 0;
		while (j < data.map_width)
		{
			map[0][i][j].z += -data.min_z;
			j++;
		}
		i++;
	}
}

static void	get_z_limits(t_vec3f **map, t_data *data)
{
	int	i;
	int	j;
	int	max_buff;
	int	min_buff;

	i = 0;
	max_buff = map[0][0].z;
	min_buff = map[0][0].z;
	while (map[i] != NULL)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (map[i][j].z > max_buff)
				max_buff = map[i][j].z;
			if (map[i][j].z < min_buff)
				min_buff = map[i][j].z;
			j++;
		}
		i++;
	}
	data->max_z = max_buff;
	data->min_z = min_buff;
	if (min_buff < 0)
		z_scale(&map, *data);
	data->min_z = 0;
}

static void	assign_map(t_vec3f ***map, char **data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (data[i] && *data[i] != '\0')
	{
		j = 0;
		tmp = ft_split(data[i], ' ');
		while (tmp[j] && *tmp[j] != '\0')
		{
			map[0][i][j].x = j;
			map[0][i][j].y = i;
			map[0][i][j].z = ft_atoi(tmp[j]);
			j++;
		}
		ft_memdel_strptr(tmp);
		i++;
	}
	check_for_dents(data, map);
	ft_memdel_strptr(data);
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

void	print_map(t_vec3f **map, int w)
{
	for (int i = 0; map[i] ; i++)
	{
		for (int j = 0 ; j < w ; j++)
		{
			printf("(%.1f, %.1f, %.1f)  ", map[i][j].x,
			       map[i][j].y, map[i][j].z);
		}
		printf("\n");
	}

}

void	get_data(char *source_file, t_data *data)
{
	int		fd;
	int		width;
	int		height;
	t_vec3f	**map;
	char	**file_content;

	fd = open(source_file, O_RDONLY);
	height = 0;
	width = 0;
	file_content = get_file_contents(fd, &width, &height);
	close(fd);
	data->map_width = width;
	data->map_height = height;
	map = (t_vec3f **)malloc((height + 1) * sizeof(t_vec3f *));
	map[height] = NULL;
	while (height--)
		map[height] = (t_vec3f *)malloc(width * sizeof(t_vec3f));
	assign_map(&map, file_content);
	data->map = map;
	get_z_limits(map, data);
//	printf("%d/%d\n", data->map_width, data->map_height);
//	print_map(map, data->map_width);
}
