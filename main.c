/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/20 19:11:15 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fill_pixel(t_mlx_data *md, int x, int y, unsigned int color)
{	
	if (x > 0 && x < md->width && y > 0 && y < md->height)
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

t_mlx_data	*mlx_data_init_return(t_mlx_data *md)
{
	static t_mlx_data 	actual_md;
	static t_img_prm 	actual_ip;
	static t_input		actual_input;

	md = &actual_md;

	md->ip = &actual_ip;

	md->in = &actual_input;
	md->in->center = 200;
	md->in->scale = 10;
	md->in->height = 0.2;
	md->in->a_x = 0;
	md->in->a_y = 0;
	md->in->a_z = 0;

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

void matrix_line(t_mlx_data *md,unsigned int color)
{
	int 	i;
	int 	j;


	i = 0;

	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m )
		{
			if (i + 1 < md->in->n) 
				line(md,
				md->in->matrix_p[j][i][0],
				md->in->matrix_p[j][i][1],
				md->in->matrix_p[j][i + 1][0],
				md->in->matrix_p[j][i + 1][1],
				color);
			if (j + 1 < md->in->m) 
				line(md,
				md->in->matrix_p[j][i][0],
				md->in->matrix_p[j][i][1],
				md->in->matrix_p[j + 1 ][i][0],
				md->in->matrix_p[j + 1 ][i][1],
				color);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
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

void project(t_mlx_data *md)
{
	int 	i;
	int 	j;
	double	xp;
	double	yp;
	double	zp;
	double	tempx;
	double	tempy;
	double	tempz;

	i = 0;
	j = 0;

	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m)
		{
			tempx = i;
			tempy = j;
			tempz = md->in->matrix[j][i] * md->in->height;

			xp = tempx * cos(md->in->a_z * PI / 180) - tempy * sin(md->in->a_z * PI / 180);
			yp = tempx * sin(md->in->a_z * PI / 180) + tempy * cos(md->in->a_z * PI / 180);
			zp = tempz;

			tempx = xp;
			tempy = yp;
			tempz = zp;

			yp = tempy * cos(md->in->a_x * PI / 180) - tempz * sin(md->in->a_x * PI / 180);
			zp = tempy * sin(md->in->a_x * PI / 180) + tempz * cos(md->in->a_x * PI / 180);
			xp = tempx;

			tempx = xp;
			tempy = yp;
			tempz = zp;

			zp = tempz * cos(md->in->a_y * PI / 180) - tempx * sin(md->in->a_y * PI / 180);
			xp = tempz * sin(md->in->a_y * PI / 180) + tempx * cos(md->in->a_y * PI / 180);
			yp = tempy;
	
			md->in->matrix_p[j][i][0] = (int) (md->in->center + xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int) (md->in->center + yp * md->in->scale);

			j += 1;
		}
		i += 1;
	}
}

void display(t_mlx_data *md, unsigned int color)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;

	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m)
		{
			fill_pixel(md, md->in->matrix_p[j][i][0], md->in->matrix_p[j][i][1], color);
			j += 1;
		}
		i += 1;
	}

	ft_putstr("Display\n");
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

void change_angle(t_mlx_data *md,char axis, float d_angle)
{
	ft_putstr("Changing ");
	ft_putchar(axis);
	ft_putstr(" axis angle of ");
	ft_putnbr(d_angle);
	ft_putstr("°. New angle = ");
	if (axis == 'x')
	{
		md->in->a_x += d_angle;
		ft_putnbr(md->in->a_x);
	}
	else if (axis == 'y')
	{
		md->in->a_y += d_angle;
		ft_putnbr(md->in->a_y);
	}
	else if (axis == 'z')
	{
		md->in->a_z += d_angle;
		ft_putnbr(md->in->a_z);
	}
	ft_putstr("°\n");
}

void display_change_angle(t_mlx_data *md,char axis, float d_angle)
{	
	int splits;
	int now;

	splits = 50;
	now = 0;
	while (now<splits)
	{
		now++;
		change_angle(md, axis, d_angle / splits);
		project(md);
		// img_square(md, BLACK);
		matrix_line(md,WHITE);
	}
}

void change_scale(t_mlx_data *md, float d_scale)
{
	md->in->scale *= d_scale;
}

int		call_keys(int keycode, t_mlx_data *md)
{
	if (keycode == 53)
	{
		mlx_destroy_window(md->mlx, md->win);
		exit(0);
	}
	else if (keycode == 49)
	{
		ft_putstr("SPACE	");
		img_square(md, RED);
	}
	else if (keycode == 11)
	{
		ft_putstr("B		");
		img_square(md, BLACK);
	}
	else if (keycode == 126)
	{
		ft_putstr("UP		");
		change_angle(md, 'x', 10);
	}
	else if (keycode == 125)
	{
		ft_putstr("DWN		");
		change_angle(md, 'x', -10);
	}
	else if (keycode == 124)
	{
		ft_putstr("RIGHT	");
		change_angle(md, 'y', 10);
	}
	else if (keycode == 123)
	{
		ft_putstr("LEFT	");
		change_angle(md, 'y', -10);
	}
	else if (keycode == 69)
	{
		ft_putstr("+		");
		change_scale(md,1.25);
	}
	else if (keycode == 78)
	{
		ft_putstr("-		");
		change_scale(md, 0.75);
	}
	project(md);
	img_square(md, BLACK);
	matrix_line(md,WHITE);
	return (0);
}


int			main(int ac, char **av) 
{
	static	t_mlx_data 	*md;
	
	md = mlx_data_init_return(md);

	read_input(md, ac, av);

	// change_scale(md,2);

	project(md);
	// display(md,WHITE);
	matrix_line(md,WHITE);
	
	mlx_key_hook(md->win, call_keys, md);
	mlx_loop(md->mlx);
	return(0);
}
