/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:16:40 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/08 10:04:24 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countlen(long long helper)
{
	size_t	len;

	len = 0;
	if (helper < 0)
	{
		helper = -helper;
		len++;
	}
	while (helper > 9)
	{
		helper = helper / 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char		*dest;
	long long	helper;
	size_t		len;

	helper = (long long)n;
	len = ft_countlen(helper);
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	if (helper == 0)
		dest[0] = '0';
	if (helper < 0)
	{
		helper = -helper;
		dest[0] = '-';
	}
	dest[len] = '\0';
	while (len > 0 && helper != 0)
	{
		dest[len - 1] = (helper % 10) + '0';
		helper = helper / 10;
		len--;
	}
	return (dest);
}
