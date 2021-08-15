
float	vec3f_magnitude(t_vec3f a, t_vec3f b)
{
	float	x;
	float	y;
	float	z;

	x = (b.x - a.x) * (b.x - a.x);
	y = (b.y - a.y) * (b.y - a.y);
	z = (b.z - a.z) * (b.z - a.z);
	return (sqrt(x + y + z));
}

void	iso_to_screen(t_vec3f *a, int scale1, int scale2)
{
	t_vec3f tmp = *a;
	a->x = tmp.x * (scale1 / 2) / scale2;
	a->y = tmp.y * (scale1 / 2) / scale2;
}

//	res.x += bound.x  * (WIN_W) / data.map_width;

//	res.y += boundy;
	/* if (data.map_width > data.map_height) */
	/* { */
	/* 	res.x += WIN_W / 2; */
	/* } */
	/* else */
	/* { */
	/* 	int tile_len = WIN_H / data.map_height; */
	/* 	iso_to_screen(&res, WIN_H, data.map_height); */
	/* 	if (data.map_height % 2 == 0) */
	/* 		res.x += WIN_W / 2; */
	/* 	else */
	/* 		res.x += WIN_W / 2 - 2 * tile_len; */
	/* } */
