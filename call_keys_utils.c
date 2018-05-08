/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:59:23 by nmanzini          #+#    #+#             */
/*   Updated: 2018/05/08 22:43:03 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	call_keys_arrows(int keycode, t_mlx_data *md)
{
	if (keycode == 126)
	{
		ft_putstr("UP       ");
		change_angle(md, 'x', 10);
	}
	else if (keycode == 125)
	{
		ft_putstr("DWN      ");
		change_angle(md, 'x', -10);
	}
	else if (keycode == 124)
	{
		ft_putstr("RIGHT    ");
		change_angle(md, 'y', 10);
	}
	else if (keycode == 123)
	{
		ft_putstr("LEFT     ");
		change_angle(md, 'y', -10);
	}
}

void	call_keys_rotate(int keycode, t_mlx_data *md)
{
	if (keycode == 14)
	{
		ft_putstr("E        ");
		change_angle(md, 'z', 10);
	}
	else if (keycode == 12)
	{
		ft_putstr("Q        ");
		change_angle(md, 'z', -10);
	}
}

void	call_keys_scale(int keycode, t_mlx_data *md)
{
	if (keycode == 69 || keycode == 24)
	{
		ft_putstr("+        ");
		change_scale(md, 'i', +1);
	}
	else if (keycode == 78 || keycode == 27)
	{
		ft_putstr("-        ");
		change_scale(md, 'i', -1);
	}
	else if (keycode == 43)
	{
		ft_putstr("<        ");
		change_scale(md, 'd', -1);
	}
	else if (keycode == 47)
	{
		ft_putstr(">        ");
		change_scale(md, 'd', +1);
	}
}

void	call_keys_camera(int keycode, t_mlx_data *md)
{
	if (keycode == 92)
	{
		ft_putstr("9np.     ");
		change_scale(md, 'c', 1.2);
	}
	else if (keycode == 88)
	{
		ft_putstr("6np.     ");
		change_scale(md, 'c', 0.85);
	}
}

void	call_keys_center(int keycode, t_mlx_data *md)
{
	if (keycode == 2)
	{
		ft_putstr("D        ");
		change_center(md, 'x', +20);
	}
	else if (keycode == 0)
	{
		ft_putstr("A        ");
		change_center(md, 'x', -20);
	}
	else if (keycode == 13)
	{
		ft_putstr("W        ");
		change_center(md, 'y', -20);
	}
	else if (keycode == 1)
	{
		ft_putstr("S        ");
		change_center(md, 'y', +20);
	}
}
