/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:22:15 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/11 13:05:33 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char const *set, char c)
{
	char	*temp;

	temp = (char *)set;
	while (*temp != '\0')
	{
		if (*temp == c)
			return (1);
		temp++;
	}
	return (0);
}

static size_t	ft_beg(char const *s1, char const *set)
{
	int		setcheck;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	setcheck = ft_checkset(set, s1[0]);
	if (setcheck == 0)
		return (0);
	i++;
	while (setcheck != 0)
	{
		setcheck = ft_checkset(set, s1[i]);
		len++;
		i++;
	}
	return (len);
}

static size_t	ft_end(char const *s1, char const *set)
{
	int		setcheck;
	size_t	len;
	size_t	i;
	size_t	slen;

	len = 0;
	slen = ft_strlen(s1);
	i = slen - 1;
	setcheck = ft_checkset(set, s1[i]);
	if (setcheck == 0)
		return (0);
	i--;
	while (setcheck != 0)
	{
		setcheck = ft_checkset(set, s1[i]);
		len++;
		i--;
	}
	return (len);
}

static void	ft_cpystr(char *dest, char const *s1, size_t beglen, size_t destlen)
{
	size_t	i;

	i = 0;
	while (i < destlen)
	{
		dest[i] = s1[beglen + i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	destlen;
	size_t	beglen;
	size_t	endlen;
	size_t	i;

	i = 0;
	beglen = ft_beg(s1, set);
	if (beglen == ft_strlen(s1))
	{
		dest = malloc(1);
		dest[i] = '\0';
		return (dest);
	}
	endlen = ft_end(s1, set);
	destlen = ft_strlen(s1) - (endlen + beglen);
	dest = malloc(destlen + 1);
	if (dest == NULL)
		return (NULL);
	ft_cpystr(dest, s1, beglen, destlen);
	return (dest);
}
