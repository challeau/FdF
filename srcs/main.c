#include "../inc/fdf.h"

void	xy_to_iso(t_vec3f *a, t_vec3f *b)
{
	t_vec3f		tmp;

	tmp = *a;
	a->x = (tmp.x - tmp.y) * cosf(0.1);
	a->y = (tmp.x + tmp.y) * cosf(0.1) - tmp.z;
	tmp = *b;
	b->x = (tmp.x - tmp.y) * cosf(0.1);
	b->y = (tmp.x + tmp.y) * cosf(0.1) - tmp.z;
}

void	draw_line_down(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	t_vec3f	from;
	t_vec3f	to;
	t_vec2f	delta;
	
	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);

	from = (t_vec3f){a.x * WIN_W / data.map_width, a.y * WIN_H / data.map_height, 0};
	to = (t_vec3f){b.x * WIN_W / data.map_width, b.y * WIN_H / data.map_height, 0};
	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, from.x, from.y, GREEN);
	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, to.x, to.y, GREEN);
	/* from = (t_vec3f){a.x * (WIN_W / 2) / data.map_width, */
	/* 		 a.y * (WIN_H / 2) / data.map_height, 0}; */
	/* to = (t_vec3f){b.x * (WIN_W / 2) / data.map_width, */
	/* 	       b.y * (WIN_H / 2) / data.map_height, 0}; */

//	xy_to_iso(&from, &to);
	if (b.x < data.map_width)
	{
		while (from.x < to.x)
		{
			mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, from.x, from.y, WHITE);
			from.x += delta.x;
			from.y += delta.y;
		}
	}
}

void	draw_line_up(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	t_vec3f	from;
	t_vec3f	to;
	t_vec2f	delta;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);

	from = (t_vec3f){a.x * WIN_W / data.map_width, a.y * WIN_H / data.map_height, 0};
	to = (t_vec3f){b.x * WIN_W / data.map_width, b.y * WIN_H / data.map_height, 0};

//	xy_to_iso(&from, &to);
	if (b.y < data.map_height)
	{
		while (from.y < to.y)
		{
			mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, from.x, from.y, WHITE);
			from.x += delta.x;
			from.y += delta.y;
		}
	}
}

void	draw_line(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	if (fabs(b.y - a.y) < fabs(b.x - a.x))
	{
		if (a.x > b.x)
			draw_line_down(mlx, data, b, a);
		else
			draw_line_down(mlx, data, a, b);
	}
	else
	{
		if (a.y > b.y)
			draw_line_up(mlx, data, b, a);
		else
			draw_line_up(mlx, data, a, b);
	}
}

void	draw_map(t_mlx mlx, t_data data)
{
	t_vec2i	p;
	t_vec3f	a;
	t_vec3f	b;

	p = (t_vec2i){0, 0};
	while (p.x < data.map_height)
	{
		p.y = 0;
		while (p.y < data.map_width)
		{
			a = data.map[p.x][p.y];
			a = vec3f_add_scal(a, cos(a.z /10));
			if (p.y < data.map_width - 1)
			{
				b = data.map[p.x][p.y + 1];
				b = vec3f_add_scal(b, cos(b.z / 10));
				draw_line(mlx, data, a, b);
			}
			if (p.x < data.map_height - 1)
			{
				b = data.map[p.x + 1][p.y];
				b = vec3f_add_scal(b, cos(b.z / 10));
				draw_line(mlx, data, a, b);
			}
			p.y++;
		}
		p.x++;
	}
	p = (t_vec2i){data.map_height - 1, data.map_width - 1};
	a = data.map[p.x][p.y - 1];
	a = vec3f_add_scal(a, cos(a.z /10));
	b = data.map[p.x][p.y];
	b = vec3f_add_scal(b, cos(b.z / 10));
	draw_line(mlx, data, a, b);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_data		data;

	if (ac != 2)
		error("wrong number of arguments");
	ft_putstr_fd(1, ">>> FdF: setting up...\n");
	setup(&mlx);
	get_data(av[1], &data);
	ft_putstr_fd(1, ">>> FdF: rendering...\n");

	draw_map(mlx, data);
	
	ft_putstr_fd(1, ">>> FdF: all done ! :)\n");
	ft_memdel_map(data.map);
	mlx_key_hook(mlx.win_ptr, &esc_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
