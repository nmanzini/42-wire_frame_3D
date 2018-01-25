/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 20:52:20 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 12:08:20 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Frees the list objects and the list itself
*/

char	***get_str_matrices(int m, char *file_path)
{
	int		i;
	int		fd;
	char	*line;
	char	***matrix_str;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	matrix_str = (char***)malloc(sizeof(char**) * (m + 1));
	while (i < m)
	{
		get_next_line(fd, &line);
		matrix_str[i] = ft_strsplit(line, ' ');
		i++;
		free(line);
	}
	matrix_str[i] = NULL;
	if (close(fd) == -1)
		return (NULL);
	return (matrix_str);
}

int		**str_to_int_matrix(int m, int n, char ***matrix_str)
{
	int i;
	int j;
	int **matrix;

	matrix = (int**)malloc(sizeof(int*) * m);
	i = 0;
	while (i < m)
	{
		matrix[i] = (int*)malloc(sizeof(int) * n);
		j = 0;
		while (j < n)
		{
			if (!(matrix_str[i][j]))
				return (NULL);
			matrix[i][j] = ft_atoi(matrix_str[i][j]);
			j++;
		}
		i++;
	}
	return (matrix);
}

int		**get_matrix(char *file_path, int *m, int *n)
{
	char	***matrix_str;
	int		**matrix;

	if (get_m_n(file_path, m, n))
		return (NULL);
	if (!(matrix_str = get_str_matrices(*m, file_path)))
		return (NULL);
	if (!(matrix = str_to_int_matrix(*m, *n, matrix_str)))
		return (NULL);
	return (matrix);
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
	md->in->m = 0;
	md->in->n = 0;
	md->in->matrix = NULL;
	if ((md->in->matrix = get_matrix(av[1], &md->in->m, &md->in->n)) == NULL)
	{
		ft_putstr("Invalid File\n");
		ft_putstr("usage: ./fdf file.fdf\n");
		return (2);
	}
	get_max_size(md);
	md->in->matrix_p = get_matrix_p(md->in->m, md->in->n, 2);
	ft_putstr(av[1]);
	ft_putstr(" loaded.\n");
	return (0);
}
