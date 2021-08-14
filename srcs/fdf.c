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

void	error(char *err_str)
{
	ft_putstr_fd(1, ">>> FdF: error encountered !\n\tIssue: ");
	ft_putstr_fd(1, err_str);
	ft_putstr_fd(1, "\n");
	exit(EXIT_FAILURE);
}

bool	setup(t_mlx *mlx)
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
