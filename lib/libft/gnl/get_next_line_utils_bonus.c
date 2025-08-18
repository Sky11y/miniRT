/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:15:11 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/27 13:02:12 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
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

char	*gnl_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			s++;
			return ((char *)s);
		}
		s++;
	}
	if (*s == c)
	{
		s++;
		return ((char *)s);
	}
	return (NULL);
}

void	gnl_memmove(void *dest, void *src, size_t n)
{
	size_t	i;
	char	*desttemp;
	char	*srctemp;

	desttemp = (char *)dest;
	srctemp = (char *)src;
	i = 0;
	while (i <= n)
	{
		desttemp[i] = srctemp[i];
		i++;
	}
}
