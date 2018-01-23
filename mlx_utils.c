/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:32:51 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/23 14:39:55 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_pixel(t_mlx_data *md, int x, int y, unsigned int color)
{
	if (x > 0 && x < md->width && y > 0 && y < md->height)
		md->ip->lst[y * md->width + x] = color;
}

void	img_square(t_mlx_data *md, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while (i < md->width)
	{
		j = 0;
		while (j < md->height)
		{
			fill_pixel(md, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

void	make_image(t_mlx_data *md)
{
	int		bpp;
	int		s_l;
	int		endian;

	md->ip->image = mlx_new_image(md->mlx, md->width, md->height);
	md->ip->lst = (int *)mlx_get_data_addr(md->ip->image, &bpp, &s_l, &endian);
}

void	fill_dot(t_mlx_data *md, int x, int y, int radius)
{
	int i;
	int	j;
	int cord;
	int radius2;

	i = -radius;
	radius2 = radius * radius;
	while (i < radius)
	{
		j = -radius;
		while (j < radius)
		{
			cord = (i * i) + (j * j);
			if (cord <= radius2)
				fill_pixel(md, i + x, j + y, md->in->dots_color);
			j++;
		}
		i++;
	}
}
