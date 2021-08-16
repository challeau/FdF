#include "../inc/fdf.h"

void	ft_memdel_map(t_vec3f *array)
{
	free(array);
	array = NULL;
}

void	xy_to_iso(t_vec3f *a, t_vec3f *b)
{
	t_vec3f	tmp;

	tmp = *a;
	a->x = (tmp.x - tmp.y) * cosf(0.34);
	a->y = (tmp.x + tmp.y) * cosf(0.34) - fabs(a->z);
	tmp = *b;
	b->x = (tmp.x - tmp.y) * cosf(0.34);
	b->y = (tmp.x + tmp.y) * cosf(0.34) - fabs(b->z);
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
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_data		data;
	t_env		env;

	display_ctrls();
	if (ac != 2)
		error("wrong number of arguments");
	mlx_setup(&mlx);
	get_data(av[1], &data);
	env.data = data;
	env.mlx = mlx;
	draw_map(&env);
	mlx_key_hook(mlx.win_ptr, &handle_events, &env);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
