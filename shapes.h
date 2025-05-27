/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:01:49 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/27 11:15:26 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "mini_rt.h"

typedef struct s_sphere
{
	float	radius;
	float	area;
	t_vec3f	pos;
	t_vec4	color;
} t_sphere;

typedef struct s_cylinder
{
	float	radius;
	float	area;
	float	height;
	t_vec3f	pos;
	t_vec4	color;
} t_cylinder;

typedef struct s_plane
{
	t_vec3f pos;
	t_vec3f	orientation;
	t_vec4	color;
} t_plane;

typedef union u_shape
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
} t_shape;


#endif
