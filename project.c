/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:12:19 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/26 13:53:02 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	perspective_z(t_mlx_data *md, float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempy;
	float	tempz;

	tempx = *xp;
	tempy = *yp;
	tempz = *zp - md->in->max_size * md->in->cam_d_f;
	*xp = tempx / tempz * md->in->cam_d_f * md->in->max_size;
	*yp = tempy / tempz * md->in->cam_d_f * md->in->max_size;
}

void	project_pe(t_mlx_data *md)
{
	int		i;
	int		j;
	float	xp;
	float	yp;
	float	zp;

	i = -1;
	while (++i < md->in->n)
	{
		j = -1;
		while (++j < md->in->m)
		{
			xp = i - md->in->n / 2;
			yp = j - md->in->m / 2;
			zp = md->in->matrix[j][i] * md->in->height;
			rotate_z(md, &xp, &yp, &zp);
			rotate_x(md, &xp, &yp, &zp);
			rotate_y(md, &xp, &yp, &zp);
			md->in->matrix_p[j][i][2] = (int)((zp + md->in->max_size) /
									md->in->max_size * md->in->dots_size);
			perspective_z(md, &xp, &yp, &zp);
			md->in->matrix_p[j][i][0] = (int)(md->in->c_x - xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int)(md->in->c_y - yp * md->in->scale);
		}
	}
}

void	project_is(t_mlx_data *md)
{
	int		i;
	int		j;
	float	xp;
	float	yp;
	float	zp;

	i = -1;
	while (++i < md->in->n)
	{
		j = -1;
		while (++j < md->in->m)
		{
			xp = i - md->in->n / 2;
			yp = j - md->in->m / 2;
			zp = md->in->matrix[j][i] * md->in->height;
			rotate_z(md, &xp, &yp, &zp);
			rotate_x(md, &xp, &yp, &zp);
			rotate_y(md, &xp, &yp, &zp);
			md->in->matrix_p[j][i][0] = (int)(md->in->c_x + xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int)(md->in->c_y + yp * md->in->scale);
			md->in->matrix_p[j][i][2] = (int)(md->in->dots_size);
		}
	}
}
