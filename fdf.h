/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:05:45 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/31 18:16:35 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>

typedef struct		s_image_struct
{
	int				*lst;
	void			*image;
}					t_img_prm;

typedef struct		s_str_struct
{
	int				x;
	int				y;
}					t_str;

typedef struct		s_input
{
	int				m;
	int				n;
	int				max;
	int				min;
	int				max_size;
	float			cam_d_f;
	float			a_x;
	float			a_y;
	float			a_z;
	float			scale;
	float			height;
	int				c_x;
	int				c_y;
	unsigned int	line_color;
	unsigned int	dots_color;
	unsigned int	back_color;
	int				dots_size;
	char			*name;
	char			***matrix_str;
	int				**matrix;
	int				***matrix_p;
}					t_input;

typedef struct		s_mlx_struct
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	char			type;
	t_img_prm		*ip;
	t_input			*in;
	t_str			*st;
}					t_mlx_data;

# define HEIGHT		1024
# define WIDTH		1024

# define BLACK		0x00000000
# define WHITE		0x00FFFFFF

# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

# define PR			3.14159265 / 180

/*
** main.c
*/
void				init_md_input(t_mlx_data *md);
t_mlx_data			*mlx_data_init_return(t_mlx_data *md);
void				line(t_mlx_data *md, int *p1, int *p2, unsigned int color);
void				matrix_line(t_mlx_data *md, unsigned int color);
/*
** change.c
*/
void				change_angle(t_mlx_data *md, char axis, float d_angle);
void				change_scale(t_mlx_data *md, char obj, float d_scale);
void				change_center(t_mlx_data *md, char axis, int ammount);
void				change_color(t_mlx_data *md, char obj, unsigned int color);
void				change_type(t_mlx_data *md, char obj);
/*
** project.c
*/
void				perspective_z(t_mlx_data *md, float *xp, float *yp,
									float *zp);
void				project_is(t_mlx_data *md);
void				project_pe(t_mlx_data *md);
/*
** rotation.c
*/
void				rotate_z(t_mlx_data *md, float *xp, float *yp, float *zp);
void				rotate_x(t_mlx_data *md, float *xp, float *yp, float *zp);
void				rotate_y(t_mlx_data *md, float *xp, float *yp, float *zp);
/*
** call_keys.c
*/
void				call_keys_general(int keycode, t_mlx_data *md);
void				call_keys_type(int keycode, t_mlx_data *md);
void				display(t_mlx_data *md);
int					call_keys(int keycode, t_mlx_data *md);
/*
** call_keys.c
*/
void				put_next_str(t_mlx_data *md, char *str);
void				put_str_and_int(t_mlx_data *md, char *str, int n);
void				put_strings(t_mlx_data *md);
/*
** call_keys_utils.c
*/
void				call_keys_arrows(int keycode, t_mlx_data *md);
void				call_keys_rotate(int keycode, t_mlx_data *md);
void				call_keys_scale(int keycode, t_mlx_data *md);
void				call_keys_center(int keycode, t_mlx_data *md);
void				call_keys_camera(int keycode, t_mlx_data *md);
/*
** call_keys_color.c
*/
void				call_keys_color_l(int keycode, t_mlx_data *md);
void				call_keys_color_d(int keycode, t_mlx_data *md);
void				call_keys_color_b(int keycode, t_mlx_data *md);
/*
** input.c
*/
int					read_input(t_mlx_data *md, int ac, char **av);
int					get_matrix(char *file_path, t_mlx_data *md);
int					str_to_int_matrix(t_mlx_data *md);
int					get_str_matrices(t_mlx_data *md, char *file_path);
int					***get_matrix_p(int m, int n, int o);
/*
** input_util.c
*/
int					string_c_length(char const *s, char c);
int					get_n(char *line);
int					get_m_n(char *file_path, int *m, int *n);
void				get_min_max(t_mlx_data *md);
void				get_max_size(t_mlx_data *md);
/*
** mlx_utils.c
*/
void				fill_dot(t_mlx_data *md, int x, int y, int radius);
void				make_image(t_mlx_data *md);
void				img_square(t_mlx_data *md, unsigned int color);
void				fill_pixel(t_mlx_data *md, int x, int y,
								unsigned int color);

#endif
