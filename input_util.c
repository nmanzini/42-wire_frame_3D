/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:31 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 12:04:41 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	list_str_free(char **list_str)
{
	while (*list_str != 0)
		free(list_str++);
	free(*list_str);
}

void	print_matrix_str(char ***matrix_str, int m, int n)
{
	int i;
	int j;

	i = 0;
	while (i < m)
	{
		j = 0;
		while (j < n)
		{
			ft_putstr(matrix_str[i][j]);
			ft_putchar('\t');
			j++;
		}
		ft_putchar(10);
		i++;
	}
}

void	print_matrix_int(int **matrix, int m, int n)
{
	int i;
	int j;

	i = 0;
	while (i < m)
	{
		j = 0;
		while (j < n)
		{
			ft_putnbr(matrix[i][j]);
			ft_putchar('\t');
			j++;
		}
		ft_putchar(10);
		i++;
	}
}

int		get_n(char *line)
{
	int		n;
	char	**list_str;

	n = 0;
	list_str = ft_strsplit(line, ' ');
	while (list_str[n] != NULL)
	{
		n++;
		free(list_str[n]);
	}
	free(list_str[n]);
	return (n);
}

int		get_m_n(char *file_path, int *m, int *n)
{
	int		fd;
	char	*line;
	int		n_old;

	n_old = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		*m = *m + 1;
		if (*n == 0)
			*n = get_n(line);
		else if (*n != get_n(line))
		{
			ft_putendl("Error: missing data points");
			return (-1);
		}
		free(line);
	}
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
}
