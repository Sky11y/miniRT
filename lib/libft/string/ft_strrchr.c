/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:27 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/11 13:02:37 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = NULL;
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			temp = s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return ((char *)temp);
}
