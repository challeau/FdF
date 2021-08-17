#include "../inc/fdf.h"

void	display_ctrls(void)
{
	ft_putstr_fd(1, ">>> FdF: welcome ! :)\n");
	ft_putstr_fd(1, ">>> FdF: USAGE\n");
	ft_putstr_fd(1, "\tarrows: translate image.\n");
	ft_putstr_fd(1, "\tTAB: zoom in.\n");
	ft_putstr_fd(1, "\tRETURN: zoom out.\n");
}

void	error(char *err_str, t_mlx *mlx)
{
	ft_putstr_fd(1, ">>> FdF: error encountered !\n\tIssue: ");
	ft_putstr_fd(1, err_str);
	ft_putstr_fd(1, "\n");
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	exit(EXIT_FAILURE);
}
