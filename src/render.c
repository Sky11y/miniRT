/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:03:00 by jpiensal          #+#    #+#             */
/*   Updated: 2025/07/02 13:09:43 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"

extern FILE	*infolog;

void	write_color(const t_vec3f pixel_color)
{
	float	r = clamp(pixel_color.x);
	float	g = clamp(pixel_color.y);
	float	b = clamp(pixel_color.z);

	int	rbyte = (int)(255.999 * r);
	int	gbyte = (int)(255.999 * g);
	int	bbyte = (int)(255.999 * b);

	printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

t_ray get_ray(float x, float y, const t_camera cam)
{
	t_ray r;
	const t_vec3f	pdu = cam.pixel_delta_u;
	const t_vec3f	pdv = cam.pixel_delta_v;
	const t_vec3f	p00_loc = cam.pixel00_loc;
	const t_vec3f	origin = cam.center;
	
	// Camera ray originates from cam center and directed at randomly sampled
	// point around the pixel location x, y.
	t_vec3f	offset = {random_float() - 0.5, random_float() - 0.5, 0};
	t_vec3f	x_offset = vt_multiply(pdu, offset.x + x);
	t_vec3f	y_offset = vt_multiply(pdv, offset.y + y);
	t_vec3f	total_offset = vv_add(x_offset, y_offset);
	t_vec3f	pixel_sample = vv_add(p00_loc, total_offset);
	r.origin = origin;
	r.direction = unit_vector(vv_sub(pixel_sample, r.origin));
	return r;
}

void render(const t_hittables *htbl, const t_camera cam, const t_image img)
{
	const uint16_t	img_height = img.image_height;
	const uint16_t	img_width = img.image_width;
	const float		pixel_samples_scale = 1.0f / cam.samples_per_pixel;
	const uint8_t	samples = cam.samples_per_pixel;
	t_vec3f			pixel_color;
	t_ray			r;

	for (int y = 0; y < img_height; y++)
	{
		//fprintf(infolog, "\rScanlines remaining: %d\n", img_height - y);
		for (int x = 0; x < img_width; x++)
		{
			pixel_color = (t_vec3f){0, 0, 0};
			for (int sample = 0; sample < samples; sample++)
			{
				r = get_ray(x, y, cam);
				pixel_color = vv_add(pixel_color, ray_color(r, htbl, cam.max_rays));
			}
			write_color(vt_multiply(pixel_color, pixel_samples_scale));
		}
	}
	fprintf(infolog, "\rDone.\t\t\t\n");
}
