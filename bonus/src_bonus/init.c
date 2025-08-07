#include "scene_elements.h"
/*
t_camera	*init_camera(t_camera *cam)
{
	cam->center = (t_vec3f){-30.0f, 10.0f, 100.0f};
	cam->orientation = (t_vec3f){0.5f, 0.0, -1.0};
	cam->orientation = unit_vector(cam->orientation);
	cam->fov = 70;
	cam->vup = (t_vec3f){0, 1.0f, 0};
	return (cam);
}
*/

t_renderer	*init_renderer(t_renderer *r, t_image *i)
{
	r->image_buffer = malloc(sizeof(uint32_t) * i->image_width * i->image_height);
	if (!r->image_buffer)
		exit(1);
	r->rendering = false;
	r->rendering_done = false;
	return (r);
}

/*
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
*/
