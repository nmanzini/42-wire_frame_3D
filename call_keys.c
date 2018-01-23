/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:11:28 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/23 15:03:44 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	call_keys(int keycode, t_mlx_data *md)
{
	call_keys_general(keycode, md);
	call_keys_arrows(keycode, md);
	call_keys_scale(keycode, md);
	call_keys_center(keycode, md);
	call_keys_color(keycode, md);
	project(md);
	img_square(md, BLACK);
	matrix_line(md, md->in->line_color);
	return (0);
}
