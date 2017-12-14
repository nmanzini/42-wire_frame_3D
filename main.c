/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2017/12/13 22:07:09 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fill_pixel(mlx_data *md, int x, int y, unsigned int color)
{
	md->ip->lst[y * md->width + x] = color;
}

void		img_square(mlx_data *md, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while (i < md->width)
	{
		j = 0;
		while (j < md->height)
		{
			fill_pixel(md,i,j,color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(md->mlx,md->win,md->ip->image,0,0);
}

void	make_image(mlx_data *md)
{
	int				bpp;
	int				s_l;
	int				endian;

	md->ip->image = mlx_new_image(md->mlx, md->width, md->height);
	md->ip->lst = (int *)mlx_get_data_addr(md->ip->image, &bpp, &s_l, &endian);
}

void		put_square(mlx_data *md, int color)
{
	int x;
	int y;

	y = md->height/4;
	while (y < md->height/4*3)
	{
		x = md->width/4;
		while (x < md->width/4*3)
		{
			mlx_pixel_put(md->mlx,md->win,x,y, color);
			x++;
		}
		y++;
	}

}

int			call_keys(int keycode, mlx_data *md)
{
	static int flag;

	if (keycode == 53)
	{
		mlx_destroy_window(md->mlx,md->win);
		exit(0);
	}
	if (keycode == 49)
	{
		if (flag)
		{
			flag = 0;
			put_square(md, 0x00000000);
		}
		else
		{
			flag = 1;
			put_square(md, 0x00FFFFFF);
		}
		
	}
	return (0);
}

int			main(void)
{
	void *mlx;
	void *win;
	mlx_data	*md;
	mlx_data 	actual_d;
	image_param actual_ip;

	md = &actual_d;
	md->ip = &actual_ip;

	md->width = WIDTH;
	md->height = HEIGHT;
	md->mlx = mlx_init();
	md->win = mlx_new_window(md->mlx,md->width,md->height, "mlx 42");

	make_image(md);



	img_square(md, RED);
	fill_pixel(md, 100, 100, WHITE);
	fill_pixel(md, 100, 101, WHITE);
	fill_pixel(md, 101, 100, WHITE);
	fill_pixel(md, 101, 101, WHITE);

	mlx_put_image_to_window(md->mlx,md->win,md->ip->image,0,0);
	

	mlx_key_hook(md->win, call_keys, md);
	// mlx_loop_hook;    puth a loop ino put image!
	mlx_loop(md->mlx);
	return(0);
}