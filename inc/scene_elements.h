/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:03:02 by jpiensal          #+#    #+#             */
/*   Updated: 2025/06/30 16:57:05 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

# include "mini_rt.h"
# include "shapes.h"

typedef struct s_camera
{
	t_vec3f	center;
	t_vec3f	orientation;
	t_vec3f	viewport_u;
	t_vec3f	viewport_v;
	t_vec3f	pixel_delta_u;
	t_vec3f	pixel_delta_v;
	t_vec3f	viewport_upper_left;
	t_vec3f	pixel00_loc;
	float	focal_length;
	float	fov;
	float	viewport_height;
	float	viewport_width;
	uint8_t	samples_per_pixel;
}	t_camera;

typedef struct s_image
{
	float		aspect_ratio;
	uint16_t	image_height;
	uint16_t	image_width;
}	t_image;

typedef struct s_hittables
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	uint8_t		sphere_count;
	uint8_t		cylinder_count;
	uint8_t		plane_count;
}	t_hittables;

typedef struct s_light
{
	t_vec3f	center;
	t_vec4	color;
	float	brightness;
}	t_light;

typedef struct s_ambient
{
	t_vec4	color;
	float	brigthness;
}	t_ambient;

typedef struct s_ray
{
	t_vec3f	direction;
	t_vec3f	origin;
}	t_ray;

t_vec3f		at(t_ray r, float t);
t_vec3f		ray_color(const t_ray r, const t_hittables *htbl);
void		render(const t_hittables *htbl, const t_camera cam, const t_image img);
float		hit_sphere(const t_sphere s, const t_ray r);
t_camera	init_camera(const t_image *img);

#endif
