/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:26:24 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:26:25 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_elements.h"

t_renderer	*init_renderer(t_renderer *r)
{
	r->rendr = false;
	r->rendr_done = false;
	return (r);
}
