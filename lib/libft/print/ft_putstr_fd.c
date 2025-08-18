/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:00:19 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/18 16:17:48 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (write(fd, "(null)", 6));
	while (*s != '\0')
	{
		write(fd, s, 1);
		len++;
		s++;
	}
	return (len);
}
