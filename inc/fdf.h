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

# define WIN_W 1000
# define WIN_H 1000

# define ESC 0xff1b
# define LEFT 0xff51
# define UP 0xff52
# define RIGHT 0xff53
# define DOWN 0xff54
# define BSP 0xff08
# define TAB 0xff09

# define WHITE 0xFFFFFF
# define GREEN 0x00FF00

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

typedef struct s_bres
{
	int			ax;
	int			bx;
	int			ay;
	int			by;
	int			err_2;
	int			err;
	size_t		i;
	t_vec2i		d;
}		t_bres;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
}		t_mlx;

typedef struct s_data
{
	t_vec3f	*map;
	int		map_width;
	int		map_height;
	int		map_len;
	int		min_z;
	int		max_z;
}		t_data;

typedef struct s_env
{
	t_mlx	mlx;
	t_data	data;
}		t_env;

/* PARSER */
void	get_data(char *source_file, t_data *data, t_mlx *mlx);
void	check_dimensions(int *width, int *height, char *line);
int		get_elem_nb(char *str);
void	get_z_limits(t_vec3f *map, t_data *data);
void	z_scale(t_vec3f **map, t_data data);

/* EVENTS */
int		esc_exit(t_mlx *mlx);
int		handle_events(int keycode, void *env);
void	handle_zoom(t_data *data, int keycode);

/* MESSAGES */
void	error(char *err_str, t_mlx *mlx);
void	display_ctrls(void);

/* DRAW */
void	xy_to_iso(t_vec3f *a, t_vec3f *b);
void	draw_map(t_env *env);

/* OTHERS */
void	ft_memdel_map(t_vec3f *array);

#endif
