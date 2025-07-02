/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:57:52 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/15 17:16:51 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unbr_fd(unsigned int n, int fd)
{
	unsigned int	nb;
	unsigned int	len;

	len = 0;
	nb = n;
	if (n > 9)
	{
		len += ft_unbr_fd(nb / 10, fd);
		len += ft_unbr_fd(nb % 10, fd);
	}
	else
	{
		nb += '0';
		len += write(fd, &nb, 1);
	}
	return (len);
}
