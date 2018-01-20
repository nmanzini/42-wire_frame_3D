/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 20:52:20 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/20 16:53:59 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Frees the list objects and the list itself 
*/

void	list_str_free(char **list_str)
{
	while (*list_str != 0)
		free(list_str++);
	free(*list_str);
}

/*
** Frees the list objects and the list itself 
*/

// void	list_int_free(int **list_int)
// {
// 	while (*list_int != 0)
// 		free(list_int++);
// 	free(*list_int);
// }

int get_m_n(char *file_path, int *m, int *n)
{
	int		fd;
	char	*lines;
	char	**list_str;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd,&lines) > 0)
	{
		*m = *m + 1;
		if (*n ==0)
		{
			list_str = ft_strsplit(lines,' ');
			while (*list_str != NULL)
			{
				*n = *n + 1;
				list_str++;
			}
			list_str_free(list_str);
		}
	}
	if (close(fd) == -1)
		return (-1);
	return(0);
}

char	***get_str_matrices( int m, char *file_path)
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
		get_next_line(fd,&line);
		matrix_str[i] = ft_strsplit(line,' ');
		i++;
	}
	matrix_str[i] = NULL;
	if (close(fd) == -1)
		return (NULL);
	return (matrix_str);
}

int	**str_to_int_matrix(int m, int n, char ***matrix_str)
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
			matrix[i][j] = ft_atoi(matrix_str[i][j]);
			j++;
		}
		i++;
	}
	return (matrix);
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

int	**get_matrix(char *file_path, int *m, int *n)
{
	char ***matrix_str;
	int	**matrix;

	get_m_n(file_path,m,n);
	ft_putstr("m = ");
	ft_putnbr(*m);
	ft_putstr("  n = ");
	ft_putnbr(*n);
	ft_putchar(10);

	ft_putendl("making matrix str");
	matrix_str = get_str_matrices(*m,file_path);

	ft_putendl("printing matrix str");
	print_matrix_str(matrix_str,*m,*n);

	ft_putendl("making matrix ints");
	matrix = str_to_int_matrix(*m,*n,matrix_str);

	ft_putendl("printing matrix ints");
	print_matrix_int(matrix,*m,*n);

	return (matrix);
}

int ***get_matrix_p(int m, int n, int o)
{
	int i;
	int j;
	int k;
	int ***matrix_p;

	i = 0;
	j = 0;
	k = 0;

	matrix_p = (int***)malloc(sizeof(int**) * m);
	i = 0;
	while (i < m)
	{	
		matrix_p[i] = (int**)malloc(sizeof(int*) * n);
		j = 0;
		while (j < n)
		{		
			matrix_p[i][j] = (int*)malloc(sizeof(unsigned int) * o);
			k = 0;
			while (k < o)
			{
				matrix_p[i][j][k] = 0;
				k++;
			}
			j++;
		}
		i++;
	}
	return (matrix_p);

}

void read_input(t_mlx_data *md,int ac, char **av)
{
	t_input in;

	md->in->m = 0;
	md->in->n = 0;
	md->in->matrix = NULL;
	if (ac)
		;
	
	md->in->matrix = get_matrix(av[1], &md->in->m, &md->in->n);
	md->in->matrix_p = get_matrix_p(md->in->m, md->in->n, 2);
}
