/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/22 18:19:26 by nmanzini         ###   ########.fr       */
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
	md->in->c_x = WIDTH/3;
	md->in->c_y = HEIGHT/3;
	md->in->scale = 10;
	md->in->height = 0.2;
	md->in->a_x = 20;
	md->in->a_y = 20;
	md->in->a_z = 20;
	md->in->line_color = WHITE;
	md->in->dots_color = BLUE;
	md->in->dots_size = 0;

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
	fill_dot (md,x1,y1,md->in->dots_size,md->in->dots_color);
	fill_dot (md,x2,y2,md->in->dots_size,md->in->dots_color);
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
				md->in->line_color);
			if (j + 1 < md->in->m) 
				line(md,
				md->in->matrix_p[j][i][0],
				md->in->matrix_p[j][i][1],
				md->in->matrix_p[j + 1 ][i][0],
				md->in->matrix_p[j + 1 ][i][1],
				md->in->line_color);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}


// void line_tester(t_mlx_data *md, int center, int size, int scale)
// {
// 	int i = - size;
// 	int j = - size;
// 	while (i <= size )
// 	{
// 		j = -size;
// 		while (j <= size)
// 		{
// 			line(md,center,center,center+i,center+j,WHITE);
// 			j += scale;
// 		}
// 		i += scale;
// 	}

// 	fill_dot(md,center,center,3,RED);
// }

void project(t_mlx_data *md)
{
	int 	i;
	int 	j;
	float	xp;
	float	yp;
	float	zp;
	float	tempx;
	float	tempy;
	float	tempz;

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
	
			md->in->matrix_p[j][i][0] = (int) (md->in->c_x + xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int) (md->in->c_y + yp * md->in->scale);

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

// void display_change_angle(t_mlx_data *md,char axis, float d_angle)
// {	
// 	int splits;
// 	int now;

// 	splits = 10;
// 	now = 0;
// 	while (now<splits)
// 	{
// 		now++;
// 		ft_putstr("display_change_angle ");
// 		ft_putnbr(now);
// 		ft_putchar('/');
// 		ft_putnbr(splits);
// 		ft_putstr(": ");

// 		change_angle(md, axis, d_angle / splits);
// 		project(md);
// 		img_square(md, BLACK);
// 		matrix_line(md,WHITE);
// 	}
// }

void	change_scale(t_mlx_data *md,char obj, float d_scale)
{
	ft_putstr("Changing scale of");
	if (obj == 'i')
	{
		ft_putstr("image to ");
		md->in->scale += d_scale;
		ft_putnbr(md->in->scale);
	}
	else if (obj == 'd')
	{
		ft_putstr("dots to ");
		md->in->dots_size += d_scale;
		ft_putnbr(md->in->dots_size);
	}
	ft_putchar(10);
}

void	change_center(t_mlx_data *md, char axis, int ammount)
{
	ft_putstr("Changing ");
	ft_putchar(axis);
	ft_putstr(" axis center position of ");
	ft_putnbr(ammount);
	ft_putstr(". New position = ");
	if (axis == 'x')
	{
		md->in->c_x += ammount;
		ft_putnbr(md->in->c_x);
	}
	else if (axis == 'y')
	{
		md->in->c_y += ammount;
		ft_putnbr(md->in->c_y);
	}
	ft_putchar(10);
}

void	change_color(t_mlx_data *md, char obj, unsigned int color)
{
	ft_putstr("Changing color of ");
	if (obj == 'l')
	{
		ft_putstr("lines to ");
		md->in->line_color = color;
		ft_putnbr(md->in->line_color);
	}
	else if (obj == 'd')
	{
		ft_putstr("dots to ");
		md->in->dots_color = color;
		ft_putnbr(md->in->dots_color);
	}
	ft_putnbr(color);
	ft_putstr(".\n");

	ft_putchar(10);
}

void animate_the_fucker(t_mlx_data *md,char obj, int ammount)
{
	int steps;
	int step;

	steps = 500;
	step = 0;

	while (step < steps)
	{
		ft_putendl("move x ");
		change_center(md,'x', 1);
		project(md);
		// img_square(md, BLACK);
		matrix_line(md, md->in->line_color);
		step++;
	}
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
		img_square(md, BLACK);
	}
	else if (keycode == 11)
	{
		ft_putstr("B		");
		img_square(md, BLUE);
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
	else if (keycode == 14)
	{
		ft_putstr("E	");
		change_angle(md, 'z', 10);
	}
	else if (keycode == 12)
	{
		ft_putstr("Q	");
		change_angle(md, 'z', -10);
	}
	else if (keycode == 69)
	{
		ft_putstr("+		");
		change_scale(md, 'i', +2);
	}
	else if (keycode == 78)
	{
		ft_putstr("-		");
		change_scale(md, 'i', -2);
	}
	else if (keycode == 43)
	{
		ft_putstr("+		");
		change_scale(md, 'd', -1);
	}
	else if (keycode == 47)
	{
		ft_putstr("-		");
		change_scale(md, 'd', +1);
	}
	else if (keycode == 2)
	{
		ft_putstr("D		");
		change_center(md, 'x', +20);
	}
	else if (keycode == 0)
	{
		ft_putstr("A		");
		change_center(md, 'x', -20);
	}
	else if (keycode == 13)
	{
		ft_putstr("W		");
		change_center(md, 'y', -20);
	}
	else if (keycode == 1)
	{
		ft_putstr("S		");
		change_center(md, 'y', +20);
	}
	else if (keycode == 82)
	{
		ft_putstr("0 numpad	");
		change_color(md,'l', WHITE);
	}
	else if (keycode == 83)
	{
		ft_putstr("1 numpad	");
		change_color(md,'l', RED);
	}
	else if (keycode == 84)
	{
		ft_putstr("2 numpad	");
		change_color(md,'l', GREEN);
	}
	else if (keycode == 85)
	{
		ft_putstr("3 numpad	");
		change_color(md,'l', BLUE);
	}
	else if (keycode == 36)
	{
		int step = 0;
		while (step < 500)
		{
			ft_putendl("move x ");
			change_center(md,'x', 1);
			project(md);
			// img_square(md, BLACK);
			matrix_line(md, md->in->line_color);
			step++;
		}
	}

	project(md);
	// img_square(md, BLACK);
	// matrix_line(md, md->in->line_color);
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
