#include "../inc/fdf.h"

void	ft_memdel_map(t_vec3f **array)
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

void	xy_to_iso(t_vec3f *a, t_vec3f *b)
{
	t_vec3f tmp = *a;
	a->x = (tmp.x - tmp.y) * cosf(0.5);
	tmp = *b;
	b->x = (tmp.x - tmp.y) * cosf(0.5);
}

void	iso_to_screen(t_vec3f *a, int scale1, int scale2)
{
	t_vec3f tmp = *a;
	a->x = tmp.x * (scale1 / 2) / scale2;
	a->y = tmp.y * (scale1 / 2) / scale2;
}

t_vec3f	scalev(t_vec3f a, t_data data)
{
	t_vec3f res = a;

	iso_to_screen(&res, WIN_W, data.map_width);
//	res.x += WIN_W / 2;
	/* if (data.map_width > data.map_height) */
	/* { */
	/* 	res.y += 50; */
	/* } */
	/* else */
	/* { */
	/* 	int tile_len = WIN_H / data.map_height; */
	/* 	iso_to_screen(&res, WIN_H, data.map_height); */
	/* 	if (data.map_height % 2 == 0) */
	/* 		res.x += WIN_W / 2; */
	/* 	else */
	/* 		res.x += WIN_W / 2 - 2 * tile_len; */
	/* } */
	return (res);
}

static bool	mlx_setup(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		error("initialization error");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "FdF");
	if (mlx->win_ptr == NULL)
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
	t_env		env;

	if (ac != 2)
		error("wrong number of arguments");
	mlx_setup(&mlx);
	get_data(av[1], &data);
	env.data = data;
	env.mlx = mlx;
	draw_map(mlx, data);
	mlx_key_hook(mlx.win_ptr, &handle_events, &env);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
