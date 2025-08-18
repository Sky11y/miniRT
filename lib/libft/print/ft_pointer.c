/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:11:38 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/19 11:45:55 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	puthex(uintptr_t n, int fd)
{
	if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 10 && n <= 15)
		ft_putchar_fd((n + 87), fd);
}

static int	convert_hex(uintptr_t n, int fd)
{
	int	result;

	if (n == 0)
		return (0);
	result = 1 + convert_hex(n / 16, fd);
	puthex(n % 16, fd);
	return (result);
}

int	ft_pointer(void *n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("(nil)", fd));
	ft_putstr_fd("0x", fd);
	return (convert_hex((uintptr_t)n, fd) + 2);
}
