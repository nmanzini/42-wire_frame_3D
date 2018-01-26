/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:52:42 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/26 13:53:00 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_mlx_data *md, float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempy;

	tempx = *xp;
	tempy = *yp;
	*xp = tempx * cos(md->in->a_z * PR) - tempy * sin(md->in->a_z * PR);
	*yp = tempx * sin(md->in->a_z * PR) + tempy * cos(md->in->a_z * PR);
}

void	rotate_x(t_mlx_data *md, float *xp, float *yp, float *zp)
{
	float	tempy;
	float	tempz;

	tempy = *yp;
	tempz = *zp;
	*yp = tempy * cos(md->in->a_x * PR) - tempz * sin(md->in->a_x * PR);
	*zp = tempy * sin(md->in->a_x * PR) + tempz * cos(md->in->a_x * PR);
}

void	rotate_y(t_mlx_data *md, float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempz;

	tempx = *xp;
	tempz = *zp;
	*zp = tempz * cos(md->in->a_y * PR) - tempx * sin(md->in->a_y * PR);
	*xp = tempz * sin(md->in->a_y * PR) + tempx * cos(md->in->a_y * PR);
}
