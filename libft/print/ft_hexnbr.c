/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:52:58 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/18 12:10:19 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	puthex(unsigned int n, int fd, char type)
{
	if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 10 && n <= 15)
	{
		if (type == 'X')
			ft_putchar_fd((n + 55), fd);
		if (type == 'x')
			ft_putchar_fd((n + 87), fd);
	}
}

static int	convert_hex(unsigned int n, int fd, char type)
{
	int	result;

	if (n == 0)
		return (0);
	result = 1 + convert_hex(n / 16, fd, type);
	puthex(n % 16, fd, type);
	return (result);
}

int	ft_hexnbr(unsigned int n, int fd, char type)
{
	if (n == 0)
		return (ft_putchar_fd(n + '0', fd));
	return (convert_hex(n, fd, type));
}
