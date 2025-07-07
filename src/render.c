#include "mini_rt.h"
#include "scene_elements.h"

extern FILE	*infolog;

void	write_color(const t_vec3f pixel_color)
{
	float	r = pixel_color.x;
	float	g = pixel_color.y;
	float	b = pixel_color.z;

	if (r > 0)
		r = sqrtf(r);
	else
		r = 0;
	if (g > 0)
		g = sqrtf(g);
	else
		g = 0;
	if (b > 0)
		b = sqrtf(b);
	else
		b = 0;
	//fprintf(infolog, "final color before [%f %f %f]\n", r, g, b);
	int	rbyte = (int)(256 * clamp(r, 0, 0.999));
	int	gbyte = (int)(256 * clamp(g, 0, 0.999));
	int	bbyte = (int)(256 * clamp(b, 0, 0.999));

	//fprintf(infolog, "final color after [%d %d %d]\n", rbyte, gbyte, bbyte);
	printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

t_ray get_ray(const t_camera cam, int *idx)
{
	const t_vec3f	pdu = cam.pixel_delta_u;
	const t_vec3f	pdv = cam.pixel_delta_v;
	const t_vec3f	p00_loc = cam.pixel00_center;
	const t_vec3f	origin = cam.center;
	t_vec3f			direction;
	
	// Camera ray originates from cam center and directed at randomly sampled
	// point around the pixel location x, y.
	t_vec3f	offset = {random_float() - 0.5, random_float() - 0.5, 0};
	t_vec3f	y_offset = vt_mul(pdv, offset.y + (float)idx[0]);
	t_vec3f	x_offset = vt_mul(pdu, offset.x + (float)idx[1]);
	t_vec3f	total_offset = vv_add(x_offset, y_offset);
	t_vec3f	pixel_sample = vv_add(p00_loc, total_offset);
	direction = unit_vector(vv_sub(pixel_sample, origin));
	if (idx[0] == 0 && idx[1] == 0) {
		fprintf(infolog, "Ray origin: [%f, %f, %f]\n", origin.x, origin.y, origin.z);
		fprintf(infolog, "Ray direction: [%f, %f, %f]\n", direction.x, direction.y, direction.z);
	}
	return ((t_ray){origin, direction});
}

t_vec3f get_pixel_color(const t_hittables  *htbl, const t_camera cam, int *idx)
{
	const uint16_t	samples = cam.samples_per_pixel;
	t_vec3f			pixel_color;
	uint16_t		sample_no;
	t_ray			r;
	
	pixel_color.x = 0;
	pixel_color.y = 0;
	pixel_color.z = 0;
	sample_no = 0;
	while (sample_no < samples)
	{
		r = get_ray(cam, idx);
		pixel_color = vv_add(pixel_color, ray_color(r, htbl, cam.max_rays));
		sample_no += 1;
	}
	return (pixel_color);
}

void render(const t_hittables *htbl, const t_camera cam, const t_image img)
{
	const uint16_t	img_height = img.image_height;
	const uint16_t	img_width = img.image_width;
	const float		pixel_samples_scale = 1.0f / cam.samples_per_pixel;
	t_vec3f			final_pixel_color;
	int				idx[2];
	fprintf(infolog, "height: %u\n", img_height);

	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		//fprintf(infolog, "\rScanlines remaining: %d\n", img_height - y);
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(htbl, cam, idx);
			//fprintf(infolog, "\rfinal_pixel color [%f %f %f]\n", final_pixel_color.x, final_pixel_color.y, final_pixel_color.z);
			write_color(vt_mul(final_pixel_color, pixel_samples_scale));
			idx[1] += 1;
		}
		idx[0] += 1;
	}
	fprintf(infolog, "\rDone.\t\t\t\n");
}
