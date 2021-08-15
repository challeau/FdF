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

void	xy_to_iso(t_vec3f *a, t_vec3f *b)
{
//	t_vec3f		proj_mat[3];

	t_vec3f tmp = *a;
	a->x = (tmp.x - tmp.y) * cosf(0.5);//M_PI / 2);
//	a->y = (tmp.x + tmp.y) * cosf(0.5);// - tmp.z;
	tmp = *b;
	b->x = (tmp.x - tmp.y) * cosf(0.5);//M_PI / 2);
//	b->y = (tmp.x + tmp.y) * cosf(0.5);// - tmp.z;

	/* proj_mat[0] = (t_vec3f){sqrt(2)/2, -(sqrt(2)/2), 0}; */
	/* proj_mat[1] = (t_vec3f){-(1/sqrt(6)), -(1/sqrt(6)), sqrt(2/3)}; */
	/* proj_mat[2] = (t_vec3f){0,0,1}; */
	/* *a = vec3f_mult_mat3(*a, proj_mat); */
	/* *b = vec3f_mult_mat3(*b, proj_mat); */
}

t_vec3f	scalev(t_vec3f a, t_data data)
{
	t_vec3f res;
	int scale1 = min(WIN_H, WIN_W);
	int scale2 = min(data.map_height, data.map_width);

	res.x = a.x  * (scale1 / 1.5) /  scale2;
//	res.x += (WIN_W / 2);
	res.y = a.y  * (scale1 / 1.5) /  scale2;
	res.x += (WIN_H / 2);
//	res.x = a.x * WIN_W / data.map_width;
//	res.y = a.y *WIN_H / data.map_height;
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
