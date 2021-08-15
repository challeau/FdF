#include "../inc/fdf.h"

int	esc_exit(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		ft_putstr_fd(1, ">>> FdF: cleaning up and exiting...\n");
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	return (1);
}
