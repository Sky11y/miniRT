/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:38 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/06 16:52:17 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*desttemp;
	char	*srctemp;

	desttemp = (char *)dest;
	srctemp = (char *)src;
	i = 0;
	if (desttemp < srctemp)
	{
		while (i < n)
		{
			desttemp[i] = srctemp[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			desttemp[i] = srctemp[i];
		}
	}
	return (dest);
}
