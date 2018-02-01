/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:11:28 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/31 20:22:12 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	call_keys_general(int keycode, t_mlx_data *md)
{
	if (keycode == 53)
	{
		ft_putendl("ESC      Bye bye!\n");
		mlx_destroy_window(md->mlx, md->win);
		exit(0);
	}
	else if (keycode == 50)
	{
		ft_putendl("ESC      Bye bye and may 0 leaks be with you\n");
		mlx_destroy_window(md->mlx, md->win);
		while (1)
			;
	}
	else if (keycode == 15)
	{
		ft_putendl("R	 RESET");
		md->in->a_x = 0;
		md->in->a_y = 0;
		md->in->a_z = 0;
		md->in->cam_d_f = 1;
	}
}

void	call_keys_type(int keycode, t_mlx_data *md)
{
	if (keycode == 35)
	{
		ft_putstr("P        ");
		change_type(md, 'p');
	}
	else if (keycode == 34)
	{
		ft_putstr("I        ");
		change_type(md, 'i');
	}
}

void	display(t_mlx_data *md)
{
	if (md->type == 'i')
		project_is(md);
	else if (md->type == 'p')
		project_pe(md);
	img_square(md, md->in->back_color);
	matrix_line(md, md->in->line_color);
	put_strings(md);
}

int		call_keys(int keycode, t_mlx_data *md)
{
	call_keys_general(keycode, md);
	call_keys_rotate(keycode, md);
	call_keys_arrows(keycode, md);
	call_keys_scale(keycode, md);
	call_keys_center(keycode, md);
	call_keys_color_l(keycode, md);
	call_keys_color_d(keycode, md);
	call_keys_color_b(keycode, md);
	call_keys_type(keycode, md);
	call_keys_camera(keycode, md);
	display(md);
	return (0);
}
