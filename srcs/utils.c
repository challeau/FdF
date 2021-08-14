#include "../inc/fdf.h"

void	ft_memdel_map(t_vec3f **array)
{
	t_vec3f	**array_ptr;

	array_ptr = array;
	while (*array_ptr != NULL)
	{
		free(*array_ptr);
		*array_ptr = NULL;
		array_ptr++;
	}
	free(array);
	array = NULL;
}

	/* tmp = *a; */
	/* a->x = (tmp.x - tmp.y) * cos(0.34); */
	/* a->y = (tmp.x + tmp.y) * cos(0.34) - tmp.z; */
	/* tmp = *b; */
	/* b->x = (tmp.x - tmp.y) * cos(0.34); */
	/* b->y = (tmp.x + tmp.y) * cos(0.34) - tmp.z; */


/* t_vec3f	project(t_vec3f a) */
/* { */
/* 	t_vec3f m1[3]; */
/* 	t_vec3f m2[3]; */
/* 	t_vec3f m3[3]; */
/* 	t_vec3f c; */
/* 	t_vec3f b; */

/* 	m1[0] = (t_vec3f){1, 0, 0}; */
/* 	m1[1] = (t_vec3f){0, cos(35), sin(35)}; */
/* 	m1[2] = (t_vec3f){0, -sin(35), cos(35)}; */

/* 	m2[0] = (t_vec3f){cos(45), 0, -sin(45)}; */
/* 	m2[1] = (t_vec3f){0, 1, 0}; */
/* 	m2[2] = (t_vec3f){sin(45), 0, cos(45)}; */

/* 	m3[0] = (t_vec3f){1, 0, 0}; */
/* 	m3[1] = (t_vec3f){0, 1, 0}; */
/* 	m3[2] = (t_vec3f){0, 0, 0}; */
/* 	c = vec3f_mult_mat3(vec3f_mult_mat3(a,  m1), m2); */
/* 	b = vec3f_mult_mat3(c, m3); */
/* 	return (b); */
/* } */
