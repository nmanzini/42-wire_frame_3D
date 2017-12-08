/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:13:29 by nmanzini          #+#    #+#             */
/*   Updated: 2017/12/08 17:00:36 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"

int main ()
{
	void *mlx;
	void *win;
	int height = 420;
	int width = 420;
	int x;
	int y;


	mlx = mlx_init();
	win = mlx_new_window(mlx,width,height, "mlx 42");
	y = height/4;
	while (y < height/4*3)
	{
		x = width/4;
		while (x < width/4*3)
		{
			mlx_pixel_put(mlx,win,x,y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_pixel_put(mlx,win,width/2,height/2, 0x00FFFFFF);
	mlx_loop(mlx);
}