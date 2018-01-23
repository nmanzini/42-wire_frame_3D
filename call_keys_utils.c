/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:59:23 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/23 16:11:47 by nmanzini         ###   ########.fr       */
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
	else if (keycode == 14)
	{
		ft_putstr("E		");
		change_angle(md, 'z', 10);
	}
	else if (keycode == 12)
	{
		ft_putstr("Q		");
		change_angle(md, 'z', -10);
	}
}

void	call_keys_arrows(int keycode, t_mlx_data *md)
{
	if (keycode == 126)
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
}

void	call_keys_scale(int keycode, t_mlx_data *md)
{
	if (keycode == 69)
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
}

void	call_keys_center(int keycode, t_mlx_data *md)
{
	if (keycode == 2)
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
}

void	call_keys_color(int keycode, t_mlx_data *md)
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
