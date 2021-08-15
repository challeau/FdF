#include "../inc/fdf.h"

void	error(char *err_str)
{
	ft_putstr_fd(1, ">>> FdF: error encountered !\n\tIssue: ");
	ft_putstr_fd(1, err_str);
	ft_putstr_fd(1, "\n");
	exit(EXIT_FAILURE);
}
