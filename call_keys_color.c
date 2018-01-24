/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:38:58 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/24 15:41:19 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	call_keys_color_l(int keycode, t_mlx_data *md)
{
	if (keycode == 82)
	{
		ft_putstr("0		");
		change_color(md, 'l', WHITE);
	}
	else if (keycode == 83)
	{
		ft_putstr("1		");
		change_color(md, 'l', RED);
	}
	else if (keycode == 84)
	{
		ft_putstr("2		");
		change_color(md, 'l', GREEN);
	}
	else if (keycode == 85)
	{
		ft_putstr("3		");
		change_color(md, 'l', BLUE);
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
