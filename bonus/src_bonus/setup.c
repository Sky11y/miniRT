#include "mini_rt.h"
#include "scene_elements.h"

inline static void	get_pixel00_location(t_camera *cam)
{
	t_vec3f	tmp1;
	t_vec3f	tmp2;
	t_vec3f	tmp3;
	t_vec3f	pixel_delta_sum;

	pixel_delta_sum = vv_add(cam->pixel_delta_u, cam->pixel_delta_v);
	tmp1 = vt_mul(cam->w, cam->focal_length);
	tmp2 = vv_sub(cam->center, tmp1);
	tmp3 = vv_add(vt_mul(cam->viewport_u, 0.5f), vt_mul(cam->viewport_v, 0.5f));
	cam->pixel00 = vv_sub(tmp2, tmp3);
	cam->pixel00_center = vv_add(cam->pixel00, vt_mul(pixel_delta_sum, 0.5f));
}

t_camera	*setup_camera(t_camera *cam, const t_image *img)
{
	float	half_w;
	t_vec3f	temp;

	cam->lookat = vv_add(cam->center, cam->orientation);
	temp = vv_sub(cam->center, cam->lookat);
	cam->focal_length = v_length(&temp);
	half_w = tanf(degrees_to_rad(cam->fov) * 0.5f);
	cam->viewport_width = 2.0f * half_w * cam->focal_length;
	cam->viewport_height = cam->viewport_width / img->aspect_ratio;
	cam->w = unit_vector(temp);
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
	if (img->aspect_ratio < EPSILON)
		img->aspect_ratio = 1.0f;
	return (img);
}
