/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:52:01 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/08 14:13:46 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	while (str1[i] != '\0' && i < len)
	{
		j = 0;
		while (str1[i + j] == str2[j] && (i + j) < len)
		{
			if (str2[j + 1] == '\0')
				return ((char *)str1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
