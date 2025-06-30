/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:01:49 by jpiensal          #+#    #+#             */
/*   Updated: 2025/06/30 16:59:23 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "mini_rt.h"

typedef struct s_sphere
{
	t_vec3f	center;
	t_vec4	color;
	float	radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3f	center;
	t_vec4	color;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3f	pos;
	t_vec3f	orientation;
	t_vec4	color;
}	t_plane;

#endif
