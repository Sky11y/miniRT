/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:28:01 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/11 13:04:20 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;
	size_t	fullsize;

	fullsize = nmemb * size;
	if (fullsize == 0)
		return (malloc(0));
	if (fullsize / nmemb != size)
		return (NULL);
	dest = malloc(fullsize);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, '\0', fullsize);
	return (dest);
}
