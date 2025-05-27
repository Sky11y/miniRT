/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:03:02 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/27 11:42:58 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_LIGHT_H
# define CAM_LIGHT_H

# include "mini_rt.h"

typedef struct s_light
{
	t_vec3f	pos;
	float	brightness;
	t_vec4	color;
} t_light;

typedef struct s_ambient
{
	float	brigthness;
	t_vec4	color;
} t_ambient;

typedef struct s_camera
{
	t_vec3f	pos;
	t_vec3f	orientation;
	uint8_t	fov;
} t_camera;

typedef struct s_ray
{
	t_vec3f	direction;
	t_vec3f origin;
} t_ray;

#endif
