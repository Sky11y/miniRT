/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:53:15 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/06 17:05:33 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	srclen;
	size_t	deslen;
	size_t	i;

	srclen = ft_strlen(src);
	deslen = ft_strlen(dest);
	i = 0;
	if (n == 0)
		return (srclen);
	if (deslen >= n)
		return (n + srclen);
	while (src[i] != '\0' && deslen + i < n - 1)
	{
		dest[i + deslen] = src[i];
		i++;
	}
	dest[deslen + i] = '\0';
	return (deslen + srclen);
}
