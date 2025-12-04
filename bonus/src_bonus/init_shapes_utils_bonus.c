/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:27:38 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:27:39 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

void	set_material(t_material *mat, float ref, float tran, float ior)
{
	mat->reflect = ref;
	mat->transparency = tran;
	mat->ior = ior;
}
