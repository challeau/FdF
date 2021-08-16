#include "../inc/fdf.h"

static void	zoom_in(t_data *data)
{
	int		i;
	t_vec3f	tmp;

	i = 0;
	while (i < data->map_len)
	{
		tmp.x = data->map[i].x * 1.5;
		tmp.y = data->map[i].y * 1.5;
		tmp.z = data->map[i].z * 1.5;
		data->map[i] = tmp;
		i++;
	}
}

static void	zoom_out(t_data *data)
{
	int		i;
	t_vec3f	tmp;

	i = 0;
	while (i < data->map_len)
	{
		tmp.x = data->map[i].x * 0.5;
		tmp.y = data->map[i].y * 0.5;
		tmp.z = data->map[i].z * 0.5;
		data->map[i] = tmp;
		i++;
	}
}

void	handle_zoom(t_data *data, int keycode)
{
	if (keycode == TAB)
		zoom_in(data);
	if (keycode == BSP)
		zoom_out(data);
}
