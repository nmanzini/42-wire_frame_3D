/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 18:19:57 by nmanzini          #+#    #+#             */
/*   Updated: 2017/12/14 20:40:07 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_rows(char *file, char **matrix, int *x)
{
	int		fd;
	char	*line;
	int		result;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((result = get_next_line(fd, &line)))
	{
		if (result == -1)
			return(-1);
		matrix[i++] = line;
		*x += 1;
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int		number_of_rows(char *file)
{
	int		fd;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		i;
	int		y;

	y = 1;
	buff[BUFF_SIZE] = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		i = 0;
		if (ret < 0)
			return (-1);
		while (buff[i] != 0)
			if (buff[i++] == 10)
				y++;
	}
	if (close(fd) == -1)
		return (-1);
	return (y);
}

int		print_matrix_str(char **matrix,int y)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		ft_putendl(matrix[i]);
		i++;
	}
	return (0);
}

int		read_input(int ac, char **av)
{
	char **matrix;
	int x;
	int y;

	ft_putendl(av[1]);

	if (ac < 2)
	{
		ft_putendl("usage: fdf source_files");
		return (-1);
	}
	if ((y = number_of_rows(av[1])) < 0)
	{
		ft_putendl("error in number of rows");
		return (-1);
	}
	ft_putendl("allocating matrix...");
	matrix = (char**)malloc(sizeof(*matrix) * y);
	ft_putendl("getting rows...");
	get_rows(av[1], matrix, &x);
	ft_putendl("printing as strings...");
	print_matrix_str(matrix, y);
	ft_putendl("turning matrix into pixels...");

	ft_putendl("printing as pixels...");

	return (0);
}
