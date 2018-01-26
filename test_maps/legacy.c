/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:51:32 by nmanzini          #+#    #+#             */
/*   Updated: 2018/01/25 15:52:50 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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