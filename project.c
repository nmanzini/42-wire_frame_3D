/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:12:19 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/24 18:32:25 by nmanzini         ###   ########.fr       */
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

/*
** tempx = i;
** tempy = j;
** tempz = md->in->matrix[j][i] * md->in->height;
** xp = tempx * cos(md->in->a_z * PR) - tempy * sin(md->in->a_z * PR);
** yp = tempx * sin(md->in->a_z * PR) + tempy * cos(md->in->a_z * PR);
** zp = tempz;
** tempx = xp;
** tempy = yp;
** tempz = zp;
** yp = tempy * cos(md->in->a_x * PR) - tempz * sin(md->in->a_x * PR);
** zp = tempy * sin(md->in->a_x * PR) + tempz * cos(md->in->a_x * PR);
** xp = tempx;
** tempx = xp;
** tempy = yp;
** tempz = zp;
** zp = tempz * cos(md->in->a_y * PR) - tempx * sin(md->in->a_y * PR);
** xp = tempz * sin(md->in->a_y * PR) + tempx * cos(md->in->a_y * PR);
** yp = tempy;
*/

void	perspective_z(t_mlx_data *md, float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempy;
	float	tempz;

	tempx = *xp;
	tempy = *yp;
	tempz = *zp;
	*xp = tempx / tempz * md->in->cam_d_f * md->in->max_size ;
	*yp = tempy / tempz * md->in->cam_d_f * md->in->max_size ;
}

void	project_pe(t_mlx_data *md)
{
	int		i;
	int		j;
	float	xp;
	float	yp;
	float	zp;

	i = 0;
	j = 0;
	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m)
		{
			xp = i - md->in->n / 2 ;
			yp = j - md->in->m / 2 ;
			zp = md->in->matrix[j][i] * md->in->height;
			rotate_z(md, &xp, &yp, &zp);
			rotate_x(md, &xp, &yp, &zp);
			rotate_y(md, &xp, &yp, &zp);
			zp  = zp - md->in->max_size * md->in->cam_d_f;
			perspective_z(md, &xp, &yp, &zp);
			md->in->matrix_p[j][i][0] = (int)(md->in->c_x - xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int)(md->in->c_y - yp * md->in->scale);
			j += 1;
		}
		i += 1;
	}
}




void	project_is(t_mlx_data *md)
{
	int		i;
	int		j;
	float	xp;
	float	yp;
	float	zp;

	i = 0;
	j = 0;
	while (i < md->in->n)
	{
		j = 0;
		while (j < md->in->m)
		{
			xp = i - md->in->n / 2;
			yp = j - md->in->m / 2;
			zp = md->in->matrix[j][i] * md->in->height;
			rotate_z(md, &xp, &yp, &zp);
			rotate_x(md, &xp, &yp, &zp);
			rotate_y(md, &xp, &yp, &zp);
			md->in->matrix_p[j][i][0] = (int)(md->in->c_x + xp * md->in->scale);
			md->in->matrix_p[j][i][1] = (int)(md->in->c_y + yp * md->in->scale);
			j += 1;
		}
		i += 1;
	}
}