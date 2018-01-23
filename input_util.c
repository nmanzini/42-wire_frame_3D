/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:31 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/23 18:18:34 by nmanzini         ###   ########.fr       */
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
	int	n;
	char **list_str;

	n = 0;
	list_str = ft_strsplit(line, ' ');
	while (list_str[n] != NULL)
	{
		n++;
	}
	// list_str_free(list_str);
	return (n);
}

int		get_m_n(char *file_path, int *m, int *n)
{
	int		fd;
	char	*lines;
	char	**list_str;
	int		n_old;

	n_old = 0;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &lines) > 0)
	{
		*m = *m + 1;
		if (*n == 0)
			*n = get_n(lines);
		else if (*n != get_n(lines))
		{
			ft_putendl("Error: missing data points");
			return (-1);
		}
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}
