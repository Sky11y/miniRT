#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

# include "mini_rt.h"
# include "shapes.h"

typedef struct s_camera
{
	t_vec3f	center;
	t_vec3f	orientation;
	t_vec3f	lookat;
	t_vec3f	vup;
	t_vec3f	u;
	t_vec3f	v;
	t_vec3f	w;
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
	uint8_t		plane_count;
	uint8_t		sphere_count;
	uint8_t		cylinder_count;
	uint8_t		obj_count;
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

typedef struct s_master
{
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	t_camera	*cam;
	t_image		*img;
	t_hittables	*htbl;
	t_lights	*light;
}	t_master;

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
	t_shape		type;
	uint8_t		index;
	int8_t		face;
}	t_hit_record;

typedef struct s_parser
{
	t_hittables	*hittables;
	t_lights	*lights;
	t_camera	*camera;
	uint8_t		amb_count;
	uint8_t		cam_count;
	uint8_t		lig_count;
}	t_parser;

/* PARSING */
int			parse_file(char *filename, t_parser *parser);
bool		line_first(char *line, char *value, int len);
int			print_error(char *error_msg);

/* INIT SHAPES */
int			init_shapes(char *filename, t_parser *parser);
int			init_ambient(t_parser *parser, char **file);
int			init_camera(t_parser *parser, char **file);
int			init_light(t_parser *parser, char **file);
int			init_plane(t_parser *parser, char **file);
int			init_sphere(t_parser *parser, char **file);
int			init_cylinder(t_parser *parser, char **file);
int			init_color(char *str, t_vec3f *color);
int			init_brightness(char *str, float *brightness);
int			init_vector(char *str, t_vec3f *vector, bool limit);
int			init_radius(char *str, float *radius);

/* UTILS */
void		rt_cleanup(t_parser *master);
char		*wrap_join(char *s1, char *s2);
int			is_float(char *str);
int			string_to_color(char *str);
float		rt_atof(char *str);
char		*get_line(char *type, char **file, int size);
char		**file_to_array(char *filename);
void		set_colors(char *str, int i, t_vec3f *colors);
int			set_vector(t_vec3f *vec, char **values, bool limit);
int			count_values(char **split);

t_vec3f		at(t_ray r, float t);
void		render(t_master *master, mlx_image_t *mlx_img);
void		update_hr(const t_hittables *htbl, t_hit_record *hr,
				const t_ray r, const float t);
t_camera	*setup_camera(t_camera *cam, const t_image *img);
t_image		*setup_image(t_image *img, uint16_t width, uint16_t height);
t_lights	*init_lights(t_lights *l);

/* HIT OBJECTS */
void		hit_all_cylinders(const t_ray r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_cylinder_caps(const t_ray r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_spheres(const t_ray r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_planes(const t_ray r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
float		count_light(const t_vec3f normal, const t_vec3f hp,
				const t_lights *light, const t_hittables *htbl);

#endif
