/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/31 18:13:34 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_md_input(t_mlx_data *md)
{
	md->in->c_x = WIDTH / 2;
	md->in->c_y = HEIGHT / 2;
	md->in->scale = +20;
	md->in->height = 0.2;
	md->in->a_x = 0;
	md->in->a_y = 0;
	md->in->a_z = 0;
	md->in->cam_d_f = 2;
	md->in->line_color = WHITE;
	md->in->dots_color = RED;
	md->in->back_color = BLACK;
	md->in->dots_size = 0;
}

t_mlx_data	*mlx_data_init_return(t_mlx_data *md)
{
	static t_mlx_data	actual_md;
	static t_img_prm	actual_ip;
	static t_input		actual_input;
	static t_str		actual_str;

	md = &actual_md;
	md->ip = &actual_ip;
	md->in = &actual_input;
	md->st = &actual_str;
	md->width = WIDTH;
	md->height = HEIGHT;
	init_md_input(md);
	md->type = 'p';
	md->mlx = mlx_init();
	md->win = mlx_new_window(md->mlx, md->width, md->height, "fdf nmanzini");
	make_image(md);
	return (md);
}

void		line(t_mlx_data *md, int *p1, int *p2, unsigned int color)
{
	int		i;
	int		xs;
	float	slope;

	i = 0;
	xs = 1;
	if ((p2[0] - p1[0]) < 0)
		xs = -1;
	slope = (float)(p2[1] - p1[1]) / (float)(p2[0] - p1[0]);
	while (i * i < (p2[0] - p1[0]) * (p2[0] - p1[0]))
	{
		i += xs;
		fill_pixel(md, i + p1[0], slope * i + p1[1], color);
	}
	i = 0;
	xs = 1;
	if ((p2[1] - p1[1]) < 0)
		xs = -1;
	while (i * i < (p2[1] - p1[1]) * (p2[1] - p1[1]))
	{
		i += xs;
		fill_pixel(md, i / slope + p1[0], i + p1[1], color);
	}
	fill_dot(md, p1[0], p1[1], p1[2]);
	fill_dot(md, p2[0], p2[1], p2[2]);
}

void		matrix_line(t_mlx_data *md, unsigned int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m)
		{
			if (i + 1 < md->in->n)
				line(md,
				md->in->matrix_p[j][i],
				md->in->matrix_p[j][i + 1],
				md->in->line_color);
			if (j + 1 < md->in->m)
				line(md,
				md->in->matrix_p[j][i],
				md->in->matrix_p[j + 1][i],
				md->in->line_color);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

int			main(int ac, char **av)
{
	static	t_mlx_data	*md;

	md = mlx_data_init_return(md);
	if (read_input(md, ac, av))
		return (1);
	ft_putendl("\nKEY	 ACTION");
	display(md);
	mlx_key_hook(md->win, call_keys, md);
	mlx_loop(md->mlx);
	return (0);
}
