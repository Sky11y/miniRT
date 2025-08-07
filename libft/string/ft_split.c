/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:16:36 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/11 13:29:45 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **split, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	**ft_strmalloc(char **split, char const *s, char c, size_t i)
{
	size_t	size;
	size_t	j;

	j = 0;
	while (s[i] != '\0')
	{
		size = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			size++;
			i++;
		}
		split[j] = malloc(size + 1);
		if (split[j] == NULL)
		{
			ft_free(split, j);
			return (NULL);
		}
		j++;
	}
	return (split);
}

static char	**ft_cpystrs(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			split[j][k] = s[i];
			i++;
			k++;
		}
		split[j][k] = '\0';
		j++;
	}
	split[j] = 0;
	return (split);
}

static size_t	ft_arrsize(char const *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
			i++;
		size++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	size_t	arrsize;
	char	**split;

	arrsize = ft_arrsize(s, c);
	split = ft_calloc((arrsize + 1), (sizeof(char *)));
	if (split == NULL)
		return (NULL);
	ft_strmalloc(split, s, c, 0);
	ft_cpystrs(split, s, c);
	return (split);
}
