/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/19 17:21:16 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fill_pixel(t_mlx_data *md, int x, int y, unsigned int color)
{
	md->ip->lst[y * md->width + x] = color;
}

void		img_square(t_mlx_data *md, unsigned int color)
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

void		make_image(t_mlx_data *md)
{
	int				bpp;
	int				s_l;
	int				endian;

	md->ip->image = mlx_new_image(md->mlx, md->width, md->height);
	md->ip->lst = (int *)mlx_get_data_addr(md->ip->image, &bpp, &s_l, &endian);
}

void		put_square(t_mlx_data *md, int color)
{
	int x;
	int y;

	y = md->height / 4;
	while (y < md->height / 4 * 3)
	{
		x = md->width / 4;
		while (x < md->width / 4 * 3)
		{
			mlx_pixel_put(md->mlx, md->win, x, y, color);
			x++;
		}
		y++;
	}
}

int			call_keys(int keycode, t_mlx_data *md)
{
	static int flag;

	if (keycode == 53)
	{
		mlx_destroy_window(md->mlx, md->win);
		exit(0);
	}
	if (keycode == 49)
	{
		if (flag)
		{
			flag = 0;
			img_square(md, 0x00000000);
		}
		else
		{
			flag = 1;
			img_square(md, 0x00FFFFFF);
		}
	}
	return (0);
}

t_mlx_data	*mlx_data_init_return(t_mlx_data *md)
{
	static t_mlx_data 	actual_md;
	static t_img_prm 	actual_ip;

	md = &actual_md;

	md->ip = &actual_ip;
	md->width = WIDTH;
	md->height = HEIGHT;
	md->mlx = mlx_init();
	md->win = mlx_new_window(md->mlx,md->width,md->height, "fdf nmanzini");
	make_image(md);
	return (md);
} 

// void		img_square(t_mlx_data *md, unsigned int color)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < md->width)
// 	{
// 		j = 0;
// 		while (j < md->height)
// 		{
// 			fill_pixel(md, i, j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
// }

void		fill_dot(t_mlx_data *md, int x,int y,int radius, unsigned int color)
{
	int i;
	int	j;
	int cord;
	int radius2;

	i = - radius;
	radius2 = radius * radius;
	while (i < radius)
	{
		j = - radius;
		while (j < radius)
		{	
			cord = (i*i) + (j*j);
			if (cord <= radius2 )
				fill_pixel(md,i + x, j+ y, color);
			j++;
		}
		i ++;
	}
}

void		matrix_put(t_mlx_data *md, t_input input, unsigned int color)
{
	int i;
	int j;
	int scal;
	int cent;

	scal = 50;
	cent = 50;
	i = 0;
	while (i < input.n)
	{
		j = 0;
		while (j < input.m)
		{
			fill_dot(md, i * scal + cent, j * scal + cent,input.matrix[j][i] + 5, color );
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

void line(t_mlx_data *md, int x1, int y1, int x2, int y2, unsigned int color)
{
	int		i;
	int		j;
	float	x;
	float	y;
	int		xs;
	int		ys;
	float	slope;

	i = 0;
	j = 0;
	y = y2 - y1;
	x = x2 - x1;
	xs = 1;
	if (x<0)
		xs = -1;
	ys = 1;
	if (y<0)
		ys = -1;
	slope = y / x;
	while (i*i < x*x)
	{
		i += xs;
		j  = slope * i;
		fill_pixel(md,  i + x1, j + y1 ,color);
	}
	i = 0;
	j = 0;
	while (j*j < y*y)
	{
		j += ys;
		i  = j / slope;
		fill_pixel(md,  i + x1, j + y1 ,color);
	}
	fill_dot (md,x1,y1,2,RED);
	fill_dot (md,x2,y2,2,RED);
}

void line_tester(t_mlx_data *md, int center, int size, int scale)
{
	int i = - size;
	int j = - size;
	while (i <= size )
	{
		j = -size;
		while (j <= size)
		{
			line(md,center,center,center+i,center+j,WHITE);
			j += scale;
		}
		i += scale;
	}

	fill_dot(md,center,center,3,RED);
}

void projection1(t_mlx_data *md,t_input input, int center, int scale, unsigned int color)
{
	int i;
	int j;
	int xp;
	int yp;
	float angle;
	float cosv;
	float sinv;

	angle= -90;
	i = 0;
	j = 0;

	cosv = cos(angle * PI / 180);
	sinv = sin(angle * PI / 180);

	while (i < input.n)
	{
		j = 0;
		while (j < input.m)
		{
			xp = center + scale * (i * cosv - j * sinv);
			yp = center + scale * (j * cosv + i * sinv);
			fill_pixel(md, xp, yp, color);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

void projection(t_mlx_data *md,t_input input, int center, int scale, unsigned int color)
{
	int 	i;
	int 	j;
	double	xp;
	double	yp;
	double	zp;
	double	anglex;
	double	angley;
	double	anglez;
	double	tempx;
	double	tempy;
	double	tempz;

	anglex = 42;
	angley = 42;
	anglez = 0;
	i = 0;
	j = 0;

	while (i < input.n)
	{
		j = 0;
		while (j < input.m)
		{

			tempx = i;
			tempy = j;
			tempz = input.matrix[j][i];

			xp = tempx * cos(anglez * PI / 180) - tempy * sin(anglez * PI / 180);
			yp = tempx * sin(anglez * PI / 180) + tempy * cos(anglez * PI / 180);
			zp = tempz;

			tempx = xp;
			tempy = yp;
			tempz = zp;

			yp = tempy * cos(anglex * PI / 180) - tempz * sin(anglex * PI / 180);
			zp = tempy * sin(anglex * PI / 180) + tempz * cos(anglex * PI / 180);
			xp = tempx;

			tempx = xp;
			tempy = yp;
			tempz = zp;

			zp = tempz * cos(angley * PI / 180) - tempx * sin(angley * PI / 180);
			xp = tempz * sin(angley * PI / 180) + tempx * cos(angley * PI / 180);
			yp = tempy;

			fill_dot(md, center + xp * scale, center + yp * scale,input.matrix[j][i]/5 + 1, color);
			
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}


int			main(int ac, char **av) 
{
	static	t_mlx_data 	*md;
	static	t_input		input;

	input = read_input(ac, av);

	md = mlx_data_init_return(md);

	projection(md,input,512,20, WHITE);

	// line_tester(md,512,400,50);

	// img_square(md, GREEN);

	// matrix_put(md,input,WHITE);

	
	mlx_put_image_to_window(md->mlx,md->win,md->ip->image,0,0);
	
	mlx_key_hook(md->win, call_keys, md);
	// mlx_loop_hook;
	mlx_loop(md->mlx);
	return(0);
}
