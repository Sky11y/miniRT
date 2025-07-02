/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:40:08 by lguillen          #+#    #+#             */
/*   Updated: 2025/02/07 10:42:07 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_arr(char **args)
{
	int	index;

	index = 0;
	while (args[index])
	{
		free(args[index]);
		index++;
	}
	free(args);
}
