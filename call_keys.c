/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:11:28 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/24 12:24:34 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	call_keys_general(int keycode, t_mlx_data *md)
{
	if (keycode == 53)
	{
		ft_putendl("ESC		Bye bye!");
		mlx_destroy_window(md->mlx, md->win);
		exit(0);
	}
	else if (keycode == 49)
	{
		ft_putstr("SPACE	");
		img_square(md, BLACK);
	}
}

void	call_keys_color_d(int keycode, t_mlx_data *md)
{
	if (keycode == 18)
	{
		ft_putstr("0		");
		change_color(md, 'd', WHITE);
	}
	else if (keycode == 19)
	{
		ft_putstr("1		");
		change_color(md, 'd', RED);
	}
	else if (keycode == 20)
	{
		ft_putstr("2		");
		change_color(md, 'd', GREEN);
	}
	else if (keycode == 21)
	{
		ft_putstr("3		");
		change_color(md, 'd', BLUE);
	}
}

void	call_keys_color_b(int keycode, t_mlx_data *md)
{
	if (keycode == 6)
	{
		ft_putstr("Z		");
		change_color(md, 'b', BLACK);
	}
	else if (keycode == 7)
	{
		ft_putstr("X		");
		change_color(md, 'b', RED);
	}
	else if (keycode == 8)
	{
		ft_putstr("C		");
		change_color(md, 'b', GREEN);
	}
	else if (keycode == 9)
	{
		ft_putstr("V		");
		change_color(md, 'b', BLUE);
	}
}

int		call_keys(int keycode, t_mlx_data *md)
{
	call_keys_general(keycode, md);
	call_keys_rotate(keycode, md);
	call_keys_arrows(keycode, md);
	call_keys_scale(keycode, md);
	call_keys_center(keycode, md);
	call_keys_color(keycode, md);
	call_keys_color_d(keycode, md);
	call_keys_color_b(keycode, md);
	project(md);
	img_square(md, md->in->back_color);
	matrix_line(md, md->in->line_color);
	return (0);
}
