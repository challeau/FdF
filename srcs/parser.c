#include "../inc/fdf.h"

static void	assign_vec(t_data *data, int index, t_vec3f a)
{
	data->map[index].x = a.x * 20 - data->map_width * 10;
	data->map[index].y = a.y * 20 - data->map_height * 10;
	data->map[index].z = a.z * 2.5;
}

static void	assign_map(t_data *data, char *file_content)
{
	static int	i = 0;
	int			j;
	char		**tmp;
	t_vec2f		last;

	j = 0;
	tmp = ft_split(file_content, ' ');
	while (tmp[j] && *tmp[j] != '\0')
	{
		assign_vec(data, j + (i * data->map_width),
			(t_vec3f){j, i, ft_atoi(tmp[j])});
		last = (t_vec2f){j, ft_atoi(tmp[j])};
		j++;
	}
	while (j < data->map_width)
	{
		assign_vec(data, j + (i * data->map_width),
			(t_vec3f){last.x, i, last.y});
		j++;
	}
	ft_memdel_strptr(tmp);
	i++;
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
	if (!content)
		error("allocation error");
	while (ret >= 0 && i < 999)
	{
		if (*line != '\0')
		{
			check_dimensions(width, height, line);
			content[i++] = ft_strdup(line);
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
	file_content[height] = NULL;
	close(fd);
	data->map_width = width;
	data->map_height = height;
	data->map_len = height * width;
	data->map = (t_vec3f *)malloc((data->map_len + 1) * sizeof(t_vec3f));
	if (!data->map)
		error("allocation error");
	while (*file_content)
	{
		assign_map(data, *file_content);
		file_content++;
	}
	ft_memdel_strptr(file_content - height);
	get_z_limits(data->map, data);
}
