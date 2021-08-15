#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define WIN_W 800
# define WIN_H 600
# define ESC 0xff1b
# define WHITE 0xFFFFFF

/* vectors and matrices */
typedef struct s_vec2f {
	float	x;
	float	y;
}		t_vec2f;

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}		t_vec3f;

typedef struct s_vec4f {
	float	x;
	float	y;
	float	z;
	float	w;
}		t_vec4f;

typedef struct s_vec2i {
	int	x;
	int	y;
}		t_vec2i;

typedef struct s_vec3i {
	int	x;
	int	y;
	int	z;
}		t_vec3i;

enum		e_axis
{
	X,
	Y,
	Z,
	__TOTAL_ROT
};

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
}		t_mlx;

typedef struct s_data
{
	t_vec3f	**map;
	int		map_width;
	int		map_height;
	int		min_z;
	int		max_z;
}		t_data;

int		esc_exit(int keycode, t_mlx *mlx);
void	error(char *err_str);

void	get_data(char *source_file, t_data *data);
void	check_max_width(int *width, char *line);
void	check_for_dents(char **data, t_vec3f ***map);
int	get_elem_nb(char *str);

t_vec3f	scalev(t_vec3f a, t_data data);
void	xy_to_iso(t_vec3f *a, t_vec3f *b);
void	draw_map(t_mlx mlx, t_data data);

/* UTILS */
float	fclampf(float value, float min, float max);
int		min(int a, int b);
int		max(int a, int b);

#endif
