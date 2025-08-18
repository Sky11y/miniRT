/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:01:42 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/06 08:56:57 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		isneg;
	long	convert;

	isneg = 1;
	convert = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			isneg = -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		convert = convert * 10 + *nptr - '0';
		if (convert < 0 && isneg == 1)
			return (-1);
		if (convert < 0 && isneg == -1)
			return (0);
		nptr++;
	}
	return ((int)(convert * isneg));
}
