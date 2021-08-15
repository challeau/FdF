#include "../inc/fdf.h"

static	void	move_x(t_data *data, int keycode)
{
	int i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (keycode == LEFT)
				data->map[i][j].x -= 1;
			else
				data->map[i][j].x += 1;
			j++;
		}
		i++;
	}
}

static	void	move_y(t_data *data, int keycode)
{
	int i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (keycode == UP)
				data->map[i][j].y -= 1;
			else
				data->map[i][j].y += 1;
			j++;
		}
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

int	esc_exit(t_mlx *mlx)
{
		ft_putstr_fd(1, ">>> FdF: cleaning up and exiting...\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(EXIT_SUCCESS);
	return (1);
}

int	handle_events(int keycd, void *env)
{
	t_env	*env_ptr;

	env_ptr = (t_env *)env;
	mlx_clear_window(env_ptr->mlx.mlx_ptr, env_ptr->mlx.win_ptr);
	if (keycd == LEFT || keycd == RIGHT || keycd == UP || keycd == DOWN)
		handle_moves(&env_ptr->data, keycd);
	if (keycd == ESC)
	{
		ft_memdel_map(env_ptr->data.map);
		esc_exit(&env_ptr->mlx);
	}
	draw_map(env_ptr->mlx, env_ptr->data);
	return (1);
}
