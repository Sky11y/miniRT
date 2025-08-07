/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:04:13 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/27 14:27:21 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	totallen;
	size_t	len1;
	size_t	len2;

	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	totallen = len1 + len2;
	dest = malloc(totallen + 1);
	if (dest == NULL)
		return (NULL);
	gnl_memcpy(dest, s1, len1);
	gnl_memcpy((dest + len1), s2, len2);
	dest[totallen] = '\0';
	free(s1);
	return (dest);
}

char	*gnl_strdup(char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = gnl_strlen(s);
	i = 0;
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*trim_next_line(char *buffer, char *stash)
{
	char	*next_line;
	char	*remainder;

	next_line = gnl_strdup(stash);
	remainder = gnl_strchr(buffer, '\n');
	gnl_memmove(buffer, remainder, gnl_strlen(remainder));
	free(stash);
	return (next_line);
}

char	*find_next_line(char *buffer, char *stash, ssize_t bytes_read, int fd)
{
	char	*next_line;

	while (bytes_read > 0)
	{
		if (gnl_strchr(buffer, '\n') != NULL)
			return (trim_next_line(buffer, stash));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			break ;
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (bytes_read == 0 && stash[0] != '\0')
		{
			next_line = gnl_strdup(stash);
			free(stash);
			return (next_line);
		}
	}
	free(stash);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*stash;
	char		*next_line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd > 1024)
		return (NULL);
	if (fd == -1)
	{
		buffer[0] = 0;
		return (NULL);
	}
	stash = malloc(1);
	if (stash == NULL)
		return (NULL);
	stash[0] = '\0';
	stash = gnl_strjoin(stash, buffer);
	next_line = find_next_line(buffer, stash, 1, fd);
	return (next_line);
}
