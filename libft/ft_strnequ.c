/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:24:32 by nmanzini          #+#    #+#             */
/*   Updated: 2017/11/22 17:16:52 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		while (*s1 == *s2 && n > 0)
		{
			if (*s1 == 0)
			{
				return (1);
			}
			s1++;
			s2++;
			n--;
		}
		if (n == 0 || (*s1 == 0 && *s2 == 0))
		{
			return (1);
		}
		return (0);
	}
	return (0);
}
