#include "scene_elements.h"

t_camera	init_camera(const t_image *img)
{
	t_camera	cam;
	t_vec3f		pixel_delta_sum;
	t_vec3f		tmp1;
	t_vec3f		tmp2;
	t_vec3f		tmp3;

	cam.center = (t_vec3f){0, 0, 0};
	cam.orientation = (t_vec3f){0, 0, 0};
	// Viewport dimensions
	cam.focal_length = 1.0f;
	cam.fov = 70;
	float half_w = tanf(degrees_to_rad(cam.fov) / 2);
	cam.viewport_width = 2.0f * half_w * cam.focal_length;
	cam.viewport_height = cam.viewport_width / img->aspect_ratio;
	cam.samples_per_pixel = 10;
	cam.max_rays = 10;
	// Calculate the vectors across the horizontal and down the vertical viewport edges
	cam.viewport_u = (t_vec3f){cam.viewport_width, 0, 0};
	cam.viewport_v = (t_vec3f){0, -cam.viewport_height, 0};

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	cam.pixel_delta_u = vt_division(cam.viewport_u, img->image_width);
	cam.pixel_delta_v = vt_division(cam.viewport_v, img->image_height);
	pixel_delta_sum = vv_add(cam.pixel_delta_u, cam.pixel_delta_v);

	// Calculate the location of the upper left pixel
	tmp1 = (t_vec3f){0, 0, cam.focal_length};
	tmp2 = vv_sub(cam.center, tmp1);
	tmp3 = vv_add(vt_division(cam.viewport_u, 2), vt_division(cam.viewport_v, 2));
	cam.viewport_upper_left = vv_sub(tmp2, tmp3);
	cam.pixel00_loc = vv_add(cam.viewport_upper_left, vt_multiply(pixel_delta_sum, 0.5));
	return (cam);
}
