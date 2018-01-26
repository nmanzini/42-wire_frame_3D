/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:57:31 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/26 16:57:43 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_next_str(t_mlx_data *md, char *str)
{
	mlx_string_put(md->mlx, md->win, md->st->x, md->st->y, WHITE, str);
	md->st->y += 18;
}

void	put_str_and_int(t_mlx_data *md, char *str, int n)
{
	char *number;
	char *str_number;

	number = ft_itoa(n);
	str_number = ft_strjoin(str, number);
	put_next_str(md, str_number);
	free(number);
	free(str_number);
}

void	put_strings(t_mlx_data *md)
{
	md->st->y = 18;
	md->st->x = 18;
	put_next_str(md, md->in->name);
	put_str_and_int(md, "X angle   = ", (int)md->in->a_x);
	put_str_and_int(md, "Y angle   = ", (int)md->in->a_y);
	put_str_and_int(md, "Z angle   = ", (int)md->in->a_z);
	put_str_and_int(md, "# Columns = ", md->in->n);
	put_str_and_int(md, "# Rows    = ", md->in->m);
	put_str_and_int(md, "Dots size = ", md->in->dots_size);
	if (md->type == 'p')
	{
		put_next_str(md, "Proj.     = Perspective");
		put_str_and_int(md, "Camera f. = ", (int)md->in->cam_d_f);
	}
	else
		put_next_str(md, "Proj.     = Parallel");
}
