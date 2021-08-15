#include "../inc/fdf.h"

static void	ft_memdel_map(t_vec3f **array)
{
	t_vec3f	**array_ptr;

	array_ptr = array;
	while (*array_ptr != NULL)
	{
		free(*array_ptr);
		*array_ptr = NULL;
		array_ptr++;
	}
	free(array);
	array = NULL;
}

float	vec3f_magnitude(t_vec3f a, t_vec3f b)
{
	float	x;
	float	y;
	float	z;

	x = (b.x - a.x) * (b.x - a.x);
	y = (b.y - a.y) * (b.y - a.y);
	z = (b.z - a.z) * (b.z - a.z);
	return (sqrt(x + y + z));
}

void	iso_to_screen(t_vec3f *a, int scale1, int scale2)
{
	t_vec3f tmp = *a;
	a->x = tmp.x * (scale1 / WIN_H / WIN_W) / scale2;
	a->y = tmp.y * (scale1 / ) / scale2;
}

void	xy_to_iso(t_vec3f *a, t_vec3f *b)
{
	t_vec3f tmp = *a;
	a->x = (tmp.x - tmp.y) * cosf(0.5);
	tmp = *b;
	b->x = (tmp.x - tmp.y) * cosf(0.5);
}

t_vec3f	scalev(t_vec3f a, t_data data)
{
	t_vec3f res = a;

	if (data.map_width > data.map_height)
	{
		iso_to_screen(&res, WIN_W, data.map_width);
		res.x += WIN_W / 2;
	}
	else
	{
		int tile_len = WIN_H / data.map_height;
		iso_to_screen(&res, WIN_H, data.map_height);
		if (data.map_height % 2 == 0)
			res.x += WIN_W / 2;
		else
			res.x += WIN_W / 2 - 2 * tile_len;
	}
	return (res);
}

static bool	mlx_setup(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		error("initialization error");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "FdF");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	if (mlx->win_ptr == NULL || mlx->img_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		return(false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_data		data;

	if (ac != 2)
		error("wrong number of arguments");
	ft_putstr_fd(1, ">>> FdF: setting up...\n");
	mlx_setup(&mlx);
	get_data(av[1], &data);
	ft_putstr_fd(1, ">>> FdF: rendering...\n");

	draw_map(mlx, data);

	ft_putstr_fd(1, ">>> FdF: all done ! :)\n");
	ft_memdel_map(data.map);
	mlx_key_hook(mlx.win_ptr, &esc_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
