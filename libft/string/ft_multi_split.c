/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:17:19 by akiiski           #+#    #+#             */
/*   Updated: 2025/07/09 15:17:23 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static _Bool	ft_haschar(char a, char *charset)
{
	int	j;

	j = 0;
	while (charset[j] != '\0')
	{
		if (a == charset[j])
			return (1);
		j++;
	}
	return (0);
}

static int	arr_size(char *str, char *charset)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (ft_haschar(str[i], charset) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		size++;
		while (!ft_haschar(str[i], charset) && str[i] != '\0')
			i++;
	}
	return (size);
}

static char	**malloc_string(char **split, char *str, char *charset, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		size = 0;
		while (ft_haschar(str[i], charset) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		size = i;
		while (!ft_haschar(str[i], charset) && str[i] != '\0')
			i++;
		size = i - size;
		split[j] = malloc(size + 1);
		if (!split[j])
		{
			free_arr(split);
			return (NULL);
		}
		j++;
	}
	return (split);
}

static char	**copy_str(char **split, char *str, char *charset)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (ft_haschar(str[i], charset) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		while (!ft_haschar(str[i], charset) && str[i] != '\0')
		{
			split[j][k] = str[i];
			k++;
			i++;
		}
		split[j][k] = '\0';
		j++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_multi_split(char *str, char *charset)
{
	char	**split;
	int		size;

	size = arr_size(str, charset);
	split = malloc((size + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	malloc_string(split, str, charset, 0);
	if (!split)
		return (NULL);
	copy_str(split, str, charset);
	return (split);
}
