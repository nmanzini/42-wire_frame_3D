/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:05:45 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/12 17:11:07 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

// check these includes1!!!!!!!!1111!!!111!1!11!
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct		s_image_struct
{
	int				*lst;
	void			*image;
}					t_img_prm;

typedef struct		s_mlx_struct
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	t_img_prm		*ip;
}					t_mlx_data;

typedef struct 		s_input
{
	int				**matrix;
	int				m;
	int				n;
}					t_input;

# define HEIGHT	1024
# define WIDTH	1024

# define BLACK	0x00000000
# define WHITE	0x00FFFFFF

# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF

t_mlx_data	*mlx_data_init_return(t_mlx_data *md);
int			call_keys(int keycode, t_mlx_data *md);
void		put_square(t_mlx_data *md, int color);
void		make_image(t_mlx_data *md);
void		img_square(t_mlx_data *md, unsigned int color);
void		fill_pixel(t_mlx_data *md, int x, int y, unsigned int color);

t_input			read_input(int ac, char **av);

#endif
