/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:34 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/06 16:19:36 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *str, size_t n)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	if (n == 0)
		return (len);
	while (str[i] != '\0' && i < n - 1)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
