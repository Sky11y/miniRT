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
	float	yaw;
	float	pitch;
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

typedef struct s_thread
{
	mlx_image_t	*mlx_img;
	t_camera	*cam;
	t_lights	*light;
	t_hittables	*htbl;
	uint16_t	row;
}	t_thread;

typedef struct s_renderer
{
	pthread_t	threads[THREAD_COUNT];
	t_thread	args[THREAD_COUNT];
	bool		rendr;
	bool		rendr_done;
}	t_renderer;

typedef struct s_master
{
	t_renderer	*renderer;
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
	t_vec3f	normal;
	t_vec3f	hitpoint;
	t_vec3f	albedo;
	t_shape	type;
	float	reflect;
	float	transparency;
	float	ior;
	uint8_t	index;
	int8_t	face;
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

/* RENDERER */
t_renderer	*init_renderer(t_renderer *r);
void		*render_thread(void *param);
void		*render_sharp(void *param);
t_ray		get_ray(const t_camera *cam, float x, float y);
t_vec3f		get_pixel_color(const t_thread *t, uint16_t *idx);
t_vec3f		ray_color(const t_ray *r, const t_thread *t, uint8_t depth);
t_vec3f		at(const t_ray *r, float t);

/* CHECK MOVES */
void		check_changes(void *param);

/* INPUT HANDLING */
void		check_keys(void *param);
void		input_keys(mlx_key_data_t kd, void *param);
void		input_mouse(double xpos, double ypos, void *param);
void		input_scroll(double xdelta, double ydelta, void *param);

/* SETUP */
t_camera	*setup_camera(t_camera *cam, const t_image *img);
t_image		*setup_image(t_image *img, uint16_t width, uint16_t height);

/* THREADS */
int			create_threads(t_master *m, t_renderer *r, int frame, bool sharp);
int			join_threads(t_renderer *r);

/* HIT OBJECTS */
void		hit_all_cylinders(const t_ray *r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_cylinder_caps(const t_ray *r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_spheres(const t_ray *r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);
void		hit_all_planes(const t_ray *r, float *closest_t,
				const t_hittables *htbl, t_hit_record *hr);

/* UPDATE HITS */
void		update_hr(const t_hittables *htbl, t_hit_record *hr,
				const t_ray *r, const float t);
float		count_light(const t_vec3f normal, const t_vec3f hp,
				const t_lights *light, const t_hittables *htbl);

/* NEW RAYS */
t_vec3f		reflect(const t_vec3f v, const t_vec3f n);
t_vec3f		refract_dir(const t_vec3f v, const t_vec3f n, const float ior,
				const int front_face);
t_vec3f		reflection(const t_ray *r, const t_thread *t,
				const t_hit_record *hr, uint8_t depth);
t_vec3f		refraction(const t_ray *r, const t_thread *t,
				const t_hit_record *hr, uint8_t depth);
t_vec3f		reflect_and_refract(const t_ray *r, const t_thread *t,
				const t_hit_record *hr, uint8_t depth);
float		schlick_prob(const t_vec3f v, const t_vec3f n, const float ior);

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
int			init_material(char *str, t_material *mat);

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
void		set_material(t_material *mat, float ref, float tran, float ior);

#endif
