/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:47:29 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/04 13:36:14 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	temp2;

	i = 0;
	temp1 = (unsigned char *)s;
	temp2 = (unsigned char)c;
	while (i < n)
	{
		if (*temp1 == temp2)
			return (temp1);
		temp1++;
		i++;
	}
	return (NULL);
}
