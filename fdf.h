/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:05:45 by nmanzini          #+#    #+#             */
/*   Updated: 2017/12/13 20:57:52 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
// check these includes1!!!!!!!!1111!!!111!1!11!
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct		image_data_s
{
	int				*lst;
	void			*image;
}					image_param;

typedef struct		data_s
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	image_param		*ip;
}					mlx_data;



# define HEIGHT	1024
# define WIDTH	1024

# define BLACK	0x00000000
# define WHITE	0x00FFFFFF

# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF

#endif