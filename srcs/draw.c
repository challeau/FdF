#include "../inc/fdf.h"

static void	draw_line_down(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	t_vec3f	from;
	t_vec3f	to;
	t_vec2f	delta;

	from = scalev(a, data);
	to = scalev(b, data);
	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	if (b.x <= data.map_width)
	{
		while (from.x <= to.x)
		{
			mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr,
				      from.x, from.y, WHITE);
			from.x += delta.x;
			from.y += delta.y;
		}
	}
}

static void	draw_line_up(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	t_vec3f	from;
	t_vec3f	to;
	t_vec2f	delta;

	from = scalev(a, data);
	to = scalev(b, data);
	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	if (b.y <= data.map_height)
	{
		while (from.y <= to.y)
		{
			mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr,
				      from.x, from.y, WHITE);
			from.x += delta.x;
			from.y += delta.y;
		}
	}
}

static void	draw_line(t_mlx mlx, t_data data, t_vec3f a, t_vec3f b)
{
	xy_to_iso(&a, &b);
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return ;
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

/*
** smaller offset == higher peak
*/
static t_vec3f	give_depth(t_vec3f a, t_data data)
{
	t_vec3f	res;
	int		offset;

	offset = data.max_z / 2;
	if (data.max_z <= 1)
		offset = 10;
	res.x = a.x + cos(a.z / offset);
	res.y = a.y + cos(a.z / offset);
	res.z = a.z;
	return (res);
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
			a = give_depth(data.map[p.x][p.y], data);
			if (p.y < data.map_width - 1)
			{
				b = give_depth(data.map[p.x][p.y + 1], data);
				draw_line(mlx, data, a, b);
			}
			if (p.x < data.map_height - 1)
			{
				b = give_depth(data.map[p.x + 1][p.y], data);
				draw_line(mlx, data, a, b);
			}
			p.y++;
		}
		p.x++;
	}
}
