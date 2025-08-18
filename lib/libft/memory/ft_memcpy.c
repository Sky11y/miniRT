/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:34:55 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/06 16:20:42 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*help1;
	unsigned char	*help2;

	help1 = (unsigned char *)dest;
	help2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		help1[i] = help2[i];
		i++;
	}
	return (dest);
}
