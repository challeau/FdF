#include "../inc/fdf.h"

void	draw_line_down(t_mlx mlx, __attribute__((unused))t_data data, t_vec3f a, t_vec3f b)
{
	float x;
	float y;
	int yi;
	t_vec2f delta;
	float D;
	
	delta = (t_vec2f){b.x - a.x, b.y - a.y};
	yi = 1;
	if (delta.y < 0)
	{
		yi = -1;
		delta.y = -delta.y;
	}
	D = (2 * delta.y) - delta.x;
	x = a.x;
	y = a.y;
	while (x < b.x)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y, WHITE);
		if (D > 0)
		{
			y += yi;
			D += (2 * (delta.y - delta.x));
		}
		else
			D += 2 * delta.y;
	}
}

void	draw_line_up(t_mlx mlx, __attribute__((unused))t_data data, t_vec3f a, t_vec3f b)
{
	float x;
	float y;
	int xi;
	t_vec2f delta;
	float D;
	
	delta = (t_vec2f){b.x - a.x, b.y - a.y};
	xi = 1;
	if (delta.x < 0)
	{
		xi = -1;
		delta.x = -delta.x;
	}
	D = (2 * delta.x) - delta.y;
	x = a.x;
	y = a.y;
	while (y < b.y)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y, WHITE);
		if (D > 0)
		{
			x += xi;
			D += (2 * (delta.x - delta.y));
		}
		else
			D += 2 * delta.x;
	}
}

void	draw_line_down(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	t_vec3f	from;
	t_vec3f	to;
	t_vec2f	delta;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);

//	from = (t_vec3f){a.x * WIN_W / data.map_width, a.y * WIN_H / data.map_height, 0};
//	to = (t_vec3f){b.x * WIN_W / data.map_width, b.y * WIN_H / data.map_height, 0};
	from = (t_vec3f){a.x * (WIN_W / 2) / data.map_width,
			 a.y * (WIN_H / 2) / data.map_height, 0};
	to = (t_vec3f){b.x * (WIN_W / 2) / data.map_width,
		       b.y * (WIN_H / 2) / data.map_height, 0};

	xy_to_iso(&from, &to);
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

	from = (t_vec3f){a.x * (WIN_W / 2) / data.map_width,
			 a.y * (WIN_H / 2) / data.map_height, 0};
	to = (t_vec3f){b.x * (WIN_W / 2) / data.map_width,
		       b.y * (WIN_H / 2) / data.map_height, 0};
	xy_to_iso(&from, &to);
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
