/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:31 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 18:00:28 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		string_c_length(char const *s, char c)
{
	int len;

	len = 0;
	if (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	while (*s != 0)
	{
		if (*s != c && s[-1] == c)
			len++;
		s++;
	}
	return (len);
}

int		get_m_n(char *file_path, int *m, int *n)
{
	int		fd;
	char	*line;
	int		num;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		*m = *m + 1;
		num = string_c_length(line, ' ');
		if (*n == 0)
			*n = num;
		else if (*n != num)
		{
			ft_putendl("Error: missing data points");
			return (-1);
		}
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

void	get_min_max(t_mlx_data *md)
{
	int max;
	int min;
	int i;
	int j;
	int value;

	max = md->in->matrix[0][0];
	min = md->in->matrix[0][0];
	i = 0;
	while (i < md->in->m)
	{
		j = 0;
		while (j < md->in->n)
		{
			value = md->in->matrix[i][j];
			if (value > max)
				max = value;
			else if (value < min)
				min = value;
			j++;
		}
		i++;
	}
	md->in->min = min;
	md->in->max = max;
}

void	get_max_size(t_mlx_data *md)
{
	int max_size;
	int delta_z;

	get_min_max(md);
	delta_z = md->in->max - md->in->min;
	max_size = 1;
	max_size += md->in->m * md->in->m;
	max_size += md->in->n * md->in->n;
	max_size += delta_z * delta_z;
	md->in->max_size = sqrt(max_size);
	md->in->scale = md->height / (float)md->in->max_size;
}
