/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 20:52:20 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 16:50:55 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Frees the list objects and the list itself
*/

int		get_str_matrices(t_mlx_data *md, char *file_path)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	md->in->matrix_str = (char***)malloc(sizeof(char**) * md->in->m);
	while (get_next_line(fd, &line) > 0)
	{
		md->in->matrix_str[i++] = ft_strsplit(line, ' ');
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int		str_to_int_matrix(t_mlx_data *md)
{
	int i;
	int j;

	md->in->matrix = (int**)malloc(sizeof(int*) * md->in->m);
	i = 0;
	while (i < md->in->m)
	{
		md->in->matrix[i] = (int*)malloc(sizeof(int) * md->in->n);
		j = 0;
		while (j < md->in->n)
		{
			if (!(md->in->matrix_str[i][j]))
				return (1);
			md->in->matrix[i][j] = ft_atoi(md->in->matrix_str[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

int		get_matrix(char *file_path, t_mlx_data *md)
{
	int		**matrix;

	md->in->m = 0;
	md->in->n = 0;
	if (get_m_n(file_path, &md->in->m, &md->in->n))
		return (1);
	if (get_str_matrices(md, file_path))
		return (1);
	if (str_to_int_matrix(md))
		return (1);
	return (0);
}

int		***get_matrix_p(int m, int n, int o)
{
	int	i;
	int	j;
	int	k;
	int	***matrix_p;

	i = 0;
	j = 0;
	k = 0;
	matrix_p = (int***)malloc(sizeof(int**) * m);
	while (i < m)
	{
		matrix_p[i] = (int**)malloc(sizeof(int*) * n);
		j = 0;
		while (j < n)
		{
			matrix_p[i][j] = (int*)malloc(sizeof(unsigned int) * o);
			k = 0;
			while (k < o)
				matrix_p[i][j][k++] = 0;
			j++;
		}
		i++;
	}
	return (matrix_p);
}

int		read_input(t_mlx_data *md, int ac, char **av)
{
	t_input in;

	if (ac < 2)
	{
		ft_putstr("usage: ./fdf file.fdf\n");
		return (1);
	}
	if (get_matrix(av[1], md))
	{
		ft_putstr("Invalid File\n");
		ft_putstr("usage: ./fdf file.fdf\n");
		return (2);
	}
	get_max_size(md);
	md->in->matrix_p = get_matrix_p(md->in->m, md->in->n, 3);
	ft_putstr(av[1]);
	ft_putstr(" loaded.\n");
	return (0);
}
