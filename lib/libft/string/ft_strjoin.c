/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:54:03 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/08 14:09:00 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	totallen;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	totallen = len1 + len2;
	dest = malloc(totallen + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, len1);
	ft_memcpy((dest + len1), s2, len2);
	dest[totallen] = '\0';
	return (dest);
}
