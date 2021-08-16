#include "../inc/fdf.h"


static void	execute_loop(t_bres draw_var, t_env *env, int clr)
{
	while (true)
	{
//		printf("%i %i\n", draw_var.ax, draw_var.ay);
		mlx_pixel_put(env->mlx.mlx_ptr, env->mlx.win_ptr,
			      draw_var.ax, draw_var.ay, clr);
		draw_var.err_2 = draw_var.err;
		if (draw_var.ax == draw_var.bx && draw_var.ay == draw_var.by)
			break ;
		if (draw_var.err_2 > -draw_var.d.x)
		{
			draw_var.err -= draw_var.d.y;
			if (draw_var.ax < draw_var.bx)
				draw_var.ax++;
			else if (draw_var.ax > draw_var.bx)
				draw_var.ax--;
		}
		if (draw_var.err_2 < draw_var.d.y)
		{
			draw_var.err += draw_var.d.x;
			if (draw_var.ay < draw_var.by)
				draw_var.ay++;
			else if (draw_var.ay > draw_var.by)
				draw_var.ay--;
		}
	}
}

static void	draw_line(t_env *env, t_vec3f *a, t_vec3f *b, int color)
{
	t_bres bres;

	xy_to_iso(a, b);
	a->z = a->z / 1000 + 10;
	b->z = b->z / 1000 + 10;
	if (a->z < 1 || b->z < 1)
		return ;
	bres.ax = (int)roundf(a->x / a->z) + WIN_W / 2;
	bres.bx = (int)roundf(b->x / b->z) + WIN_W / 2;
	bres.ay = (int)roundf(a->y / a->z) + WIN_H / 2;
	bres.by = (int)roundf(b->y / b->z) + WIN_H / 2;
	if ((bres.ax < 0 || bres.ax > WIN_W || bres.ay < 0 ||
		bres.ay > WIN_W) && (bres.bx < 0 || bres.bx > WIN_W ||
					 bres.by < 0 || bres.by > WIN_H / 2))
		return ;
	bres.i = 0;
	bres.d.x = abs(bres.bx - bres.ax);
	bres.d.y = abs(bres.by - bres.ay);
	bres.err = ((bres.d.x > bres.d.y ? bres.d.x : -bres.d.y)) >> 1;
	execute_loop(bres, env, color);
}


void	draw_map(t_env *env)
{
	int	i;
	t_vec3f	a;
	t_vec3f	b;

	i = 0;
	while (i < env->data.map_len)
	{
		if (i + env->data.map_width < env->data.map_len)   // draw down
		{
			a = env->data.map[i];
			b = env->data.map[i + env->data.map_width];
				draw_line(env, &a, &b, WHITE);
		}
		if (i % env->data.map_width != env->data.map_width - 1)// draw right
		{
			a = env->data.map[i];
			b = env->data.map[i + 1];
				draw_line(env, &a, &b, WHITE);
		}
		i++;
	}
}
