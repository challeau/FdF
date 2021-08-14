

typedef	struct			s_var
{
	int			ax;
	int			bx;
	int			ay;
	int			by;
	int			err_2;
	int			err;
	size_t		i;
	t_vec2i		d;
}		t_var;


/* mlx passed not as pointr == possible issue */
void	execute_loop(t_var draw_var, t_mlx mlx)
{
	while (true)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, draw_var.ax, draw_var.ay, WHITE);
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
/* mlx issue ptr */
void	draw_vector(t_mlx mlx, t_data data, t_vec3f *a, t_vec3f *b)
{
	t_var dw_vr;

	a->z = a->z / 1000 + 10;
	b->z = b->z / 1000 + 10;
	if (a->z < 1 || b->z < 1)
		return ;
	dw_vr.ax = (int)roundf(a->x / a->z) + data.map_width / 2;
	dw_vr.bx = (int)roundf(b->x / b->z) + data.map_width / 2;
	dw_vr.ay = (int)roundf(a->y / a->z) + data.map_height / 2;
	dw_vr.by = (int)roundf(b->y / b->z) + data.map_height / 2;
	if ((dw_vr.ax < 0 || dw_vr.ax > data.map_width || dw_vr.ay < 0 ||
		dw_vr.ay > data.map_width) && (dw_vr.bx < 0 || dw_vr.bx > data.map_width ||
						     	dw_vr.by < 0 || dw_vr.by > 500))
		return ;
	dw_vr.i = 0;
	dw_vr.d.x = abs(dw_vr.bx - dw_vr.ax);
	dw_vr.d.y = abs(dw_vr.by - dw_vr.ay);
	dw_vr.err = ((dw_vr.d.x > dw_vr.d.y ? dw_vr.d.x : -dw_vr.d.y)) >> 1;
	execute_loop(dw_vr, mlx);
}


/* static double	get_step(double dx, double dy) */
/* { */
/* 	if (fabs(dx) >= fabs(dy)) */
/* 		return (fabs(dx)); */
/* 	else */
/* 		return (fabs(dy)); */
/* } */

