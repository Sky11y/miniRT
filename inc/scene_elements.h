#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

# include "mini_rt.h"
# include "shapes.h"

typedef struct s_camera
{
	t_vec3f	center;
	t_vec3f	orientation;
	t_vec3f lookat;
	t_vec3f vup;
	t_vec3f	u, v, w;
	t_vec3f	viewport_u;
	t_vec3f	viewport_v;
	t_vec3f	pixel_delta_u;
	t_vec3f	pixel_delta_v;
	t_vec3f	pixel00;
	t_vec3f	pixel00_center;
	float	focal_length;
	float	fov;
	float	viewport_height;
	float	viewport_width;
	uint16_t	samples_per_pixel;
	uint8_t	max_rays;
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

typedef struct s_lights
{
	t_vec3f	point_center;
	t_vec3f	point_color;
	t_vec3f	ambient_color;
	t_vec3f	ambient_tint;
	float	point_brightness;
	float	ambient_brightness;
}	t_lights;

typedef struct s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_vec3f		normal;
	t_vec3f		hitpoint;
	t_vec3f		albedo;
	uint8_t		index;
	t_shape		type;
}	t_hit_record;

t_vec3f	at(t_ray r, float t);
t_vec3f	ray_color(const t_ray r, const t_hittables *htbl,
		const t_lights *light);
t_vec3f	get_pixel_color(const t_hittables  *htbl, const t_camera *cam,
		int *idx, const t_lights *light);
void	render(const t_hittables *htbl, const t_camera *cam,
		const t_image *img, const t_lights *light);
void	update_hr(const t_hittables *htbl, t_hit_record *hr,
		const t_ray r, const float t);
t_ray	get_ray(const t_camera *cam, int *idx);
void	init_camera(t_camera *cam, const t_image *img);
void	init_image(t_image *img);
void	init_lights(t_lights *l);

/* HIT OBJECTS */
void	hit_all_cylinders(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr);
void	hit_all_cylinder_caps(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr);
void	hit_all_spheres(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr);
void	hit_all_planes(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr);
float	count_light(const t_vec3f normal, const t_vec3f hp,
		const t_lights *light);

#endif
