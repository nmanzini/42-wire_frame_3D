/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:14:06 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 17:18:32 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		change_angle(t_mlx_data *md, char axis, float d_angle)
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

void		change_scale(t_mlx_data *md, char obj, float d_scale)
{
	ft_putstr("Changing scale of");
	if (obj == 'i')
	{
		ft_putstr(" Image to ");
		if (md->in->scale + d_scale > 0)
			md->in->scale += d_scale;
		ft_putnbr(md->in->scale);
	}
	else if (obj == 'd')
	{
		ft_putstr(" Dts to ");
		if (md->in->dots_size + d_scale >= 0)
			md->in->dots_size += d_scale;
		ft_putnbr(md->in->dots_size);
	}
	else if (obj == 'c')
	{
		ft_putstr(" Camera to ");
		if (md->in->cam_d_f * d_scale >= 0.5 &&
			md->in->cam_d_f * d_scale <= 1000)
			md->in->cam_d_f *= d_scale;
		ft_putnbr(md->in->cam_d_f);
	}
	ft_putchar(10);
}

void		change_center(t_mlx_data *md, char axis, int ammount)
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

void		change_color(t_mlx_data *md, char obj, unsigned int color)
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
	else if (obj == 'b')
	{
		ft_putstr("background to ");
		md->in->back_color = color;
		ft_putnbr(md->in->back_color);
	}
	ft_putnbr(color);
	ft_putstr(".\n");
}

void		change_type(t_mlx_data *md, char obj)
{
	ft_putstr("Changing type of projection to ");
	if (obj == 'i')
	{
		ft_putstr("isometric.\n");
		md->type = 'i';
	}
	else if (obj == 'p')
	{
		ft_putstr("perspective.\n");
		md->type = 'p';
	}
}
