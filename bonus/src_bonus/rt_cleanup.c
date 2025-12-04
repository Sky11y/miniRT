/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:29:14 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:29:15 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

void	rt_cleanup(t_parser *master)
{
	free(master->lights);
	free(master->camera);
	free(master->hittables->planes);
	free(master->hittables->spheres);
	free(master->hittables->cylinders);
}
