#include "../inc/fdf.h"

int	esc_exit(t_mlx *mlx)
{
	ft_putstr_fd(1, ">>> FdF: cleaning up and exiting...\n");
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (1);
}

static	void	move_x(t_data *data, int keycode)
{
	int	i;

	i = 0;
	while (i < data->map_len)
	{
		if (keycode == LEFT)
			data->map[i].x -= 50;
		else
			data->map[i].x += 50;
		i++;
	}
}

static	void	move_y(t_data *data, int keycode)
{
	int	i;

	i = 0;
	while (i < data->map_len)
	{
		if (keycode == UP)
			data->map[i].y -= 50;
		else
			data->map[i].y += 50;
		i++;
	}
}

void	handle_moves(t_data *data, int keycode)
{
	t_data	*map_data;

	map_data = (t_data *)data;
	if (keycode == UP || keycode == DOWN)
		move_y(data, keycode);
	if (keycode == LEFT || keycode == RIGHT)
		move_x(data, keycode);
}

int	handle_events(int keycd, void *env)
{
	t_env	*env_ptr;

	env_ptr = (t_env *)env;
	mlx_clear_window(env_ptr->mlx.mlx_ptr, env_ptr->mlx.win_ptr);
	if (keycd == LEFT || keycd == RIGHT || keycd == UP || keycd == DOWN)
		handle_moves(&env_ptr->data, keycd);
	if (keycd == TAB || keycd == BSP)
		handle_zoom(&env_ptr->data, keycd);
	if (keycd == ESC)
	{
		ft_memdel_map(env_ptr->data.map);
		esc_exit(&env_ptr->mlx);
	}
	draw_map(env_ptr);
	return (1);
}
