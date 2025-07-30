#include "scene_elements.h"

// Calculate the location of the upper left pixel
inline static void	get_pixel00_location(t_camera *cam)
{
	t_vec3f	tmp1;
	t_vec3f	tmp2;
	t_vec3f	tmp3;
	t_vec3f	pixel_delta_sum;

	pixel_delta_sum = vv_add(cam->pixel_delta_u, cam->pixel_delta_v);
	tmp1 = vt_mul(cam->w, cam->focal_length);
	tmp2 = vv_sub(cam->center, tmp1);
	tmp3 = vv_add(vt_div(cam->viewport_u, 2), vt_div(cam->viewport_v, 2));
	cam->pixel00 = vv_sub(tmp2, tmp3);
	cam->pixel00_center = vv_add(cam->pixel00, vt_mul(pixel_delta_sum, 0.5));
}

t_camera	*setup_camera(t_camera *cam, const t_image *img)
{
	float	half_w;

	cam->center = (t_vec3f){-30.0f, 20.0f, 40.0f};
	cam->orientation = (t_vec3f){0.5f, -0.3, -1.0};
	cam->fov = 70;
	cam->lookat = vv_add(cam->center, cam->orientation);
	cam->vup = (t_vec3f){0, 1.0f, 0};
	cam->focal_length = v_length(vv_sub(cam->center, cam->lookat));
	half_w = tanf(degrees_to_rad(cam->fov) / 2);
	cam->viewport_width = 2.0f * half_w * cam->focal_length;
	cam->viewport_height = cam->viewport_width / img->aspect_ratio;
	cam->w = unit_vector(vv_sub(cam->center, cam->lookat));
	cam->u = unit_vector(cross(cam->vup, cam->w));
	cam->v = unit_vector(cross(cam->w, cam->u));
	cam->viewport_u = vt_mul(cam->u, cam->viewport_width);
	cam->viewport_v = vt_mul(cam->v, -cam->viewport_height);
	cam->pixel_delta_u = vt_div(cam->viewport_u, img->image_width);
	cam->pixel_delta_v = vt_div(cam->viewport_v, img->image_height);
	get_pixel00_location(cam);
	return (cam);
}

t_image	*setup_image(t_image *img, uint16_t width, uint16_t height)
{
	img->image_width = width;
	img->image_height = height;
	img->aspect_ratio = (float)width / height;
	if (img->aspect_ratio < 1e-4)
		img->aspect_ratio = 1.0f;
	return (img);
}

t_lights	*init_lights(t_lights *l)
{
	l->ambient_color = (t_vec3f){0.98f, 0.8f, 1.0f};
	l->ambient_brightness = 0.2f;
	l->ambient_tint = vt_mul(l->ambient_color, l->ambient_brightness);
	l->point_center = (t_vec3f){-40.0f, 10.2f, 30.0f};
	l->point_brightness = 0.7f;
	l->point_color = (t_vec3f){1, 1, 1};
	return (l);
}
