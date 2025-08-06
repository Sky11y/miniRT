#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

inline static bool is_window_size_changed(mlx_t *mlx)
{
	static int32_t width = WIN_WIDTH;
	static int32_t height = WIN_HEIGHT;

	if (mlx->width == width && mlx->height == height)
		return (false);
	width = mlx->width;
	height = mlx->height;
	return (true);
}

static t_renderer	*init_renderer(t_renderer *r, t_image *i)
{
	r->image_buffer = malloc(sizeof(uint32_t) * i->image_width * i->image_height);
	if (!r->image_buffer)
		exit(1);
	r->rendering = false;
	r->rendering_done = false;
	return (r);
}

static t_renderer	*setup_renderer(t_renderer *r, t_image *i)
{
	free(r->image_buffer);
	r->image_buffer = malloc(sizeof(uint32_t) * i->image_width * i->image_height);
	if (!r->image_buffer)
		exit(1);
	return (r);
}

inline static void	minirt(void *param)
{
	t_master	*m = (t_master *)param;
	t_renderer	*r = m->renderer;
	uint16_t	starting_row;
	static int	frame = 0;
	//static int	cycle = 0;
	static double previous = 0;
	bool			window_size_changed;

	window_size_changed = false;
	if (is_window_size_changed(m->mlx))
	{
		m->img = setup_image(m->img, m->mlx->width, m->mlx->height);
		m->renderer = setup_renderer(m->renderer, m->img);
		mlx_resize_image(m->mlx_img, m->mlx->width, m->mlx->height);
		window_size_changed = true;
	}
	if (window_size_changed || check_keys(m) || check_mouse(m))
	{
		m->cam = setup_camera(m->cam, m->img);
		r->rendering_done = false;
		//frame = 0;
	}
	if (!r->rendering)// && !r->rendering_done)
	{
		r->rendering = true;
		starting_row = THREAD_COUNT * THREAD_COUNT * frame;
		for (int i = 0; i < THREAD_COUNT; i++)
		{
			r->args[i] = (t_thread){
				.id = i + starting_row,
				.width = m->img->image_width,
				.height = m->img->image_height,
				.pixels = r->image_buffer,
				.cam = m->cam,
				.htbl = m->htbl,
				.light = m->light,
				.mlx_img = m->mlx_img,
			};
			pthread_create(&r->threads[i], NULL, render_thread, &r->args[i]);
			//handle errors
		}
	}
	if (r->rendering)
	{
		int count = 0;
		while (count < THREAD_COUNT)
		{
			if (pthread_join(r->threads[count++], NULL))
				exit(1);
		}
		r->rendering = false;
	}
	frame++;
	if (frame * THREAD_COUNT * THREAD_COUNT >= m->mlx->height)
	{
		frame = 0;
		r->rendering_done = true;
		double now = mlx_get_time();

		printf("render time = %lf\n", now - previous);
		previous = now;
		/*cycle++;
		if (cycle == RENDER_CYCLES) // this is needed wh
		{
			cycle = 0;
		}*/
	}

	//printf("delta time %lf\n", m->mlx->delta_time);
}

int main()
{
	t_master	master;
	t_camera	cam;
	t_image		img;
	t_renderer	r;
	t_lights	light;
	t_hittables	hittables;

	master.light = init_lights(&light);
	master.img = setup_image(&img, WIN_WIDTH, WIN_HEIGHT);
	master.cam = init_camera(&cam);
	master.cam = setup_camera(&cam, &img);
	master.renderer = init_renderer(&r, &img);
	
	/***** HERE IS THE TESTS FOR DIFFERENT HITTABLE OBJECTS *****/

	//TESTING THE SCHOOL SUBJECT EXAMPLE
	hittables.cylinder_count = 1;
	hittables.sphere_count = 3;
	hittables.plane_count = 2;

	t_cylinder c1 = {
		{30.0f, 0.0f, -20.6f},		//position
		{0.0f, 1.0f, 1.0f},	//orientation
		{0, 0, 0},			//base point -> initialised to zero and calculated later
		{10.0 / 255, 0.0f, 1.0f},		//color
		{0.3f, 0.0f},				//material {reflection, refraction}
		14.2,				//radius 
		14.2f * 14.2f,		//radius squared
		21.42f,				//height
	};
	/*
	t_cylinder c2 = {
		{-1.2, 0.0, 3},
		{0.2, 1.0, 0.6},
		{0, 0, 0},
		{1.0, 0, 0},
		{{1.0f, 0.0f}},
		0.5f,
		0.5f * 0.5f,
		0.5f,
		0.4f,
		METAL,
	};*/
	c1.axis_v = unit_vector(c1.axis_v);
	c1.base  = vv_sub(c1.center, vt_mul(c1.axis_v, c1.height / 2));
	//c2.axis_v = unit_vector(c2.axis_v);
	//c2.base  = vv_sub(c2.center, vt_mul(c2.axis_v, c2.height / 2));
	t_cylinder *cylinders = malloc(sizeof(t_cylinder) * hittables.cylinder_count);	
	cylinders[0] = c1;
	//cylinders[1] = c2;
	//
	t_plane p1 = {
		{0.0f, -25.0f, 0.0f},		//position
		{0.0f, 1.0f, 0.0f},	//orientation
		{1.0f, 1.0f, 1.0f},		//color
		{0.2f, 0.0f},		//material
	};
	t_plane p2 = {
		{0.0f, 0.0f, -600.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f},
	};
	p1.orientation = unit_vector(p1.orientation);
	p2.orientation = unit_vector(p2.orientation);
	t_plane	*planes = malloc(sizeof(t_plane) * hittables.plane_count);	
	planes[0] = p1;
	planes[1] = p2;

	t_sphere s1 = {
		{0.0f, 0.0f, -20.0f},	//position
		{1.0f, 1.0f, 1.0f},	//color
		{0.0f, 0.7f},		//material
		20.0f,			//radius
		20.0f * 20.f,	//radius_squared
	};
	
	t_sphere s2 = {
		{0.0f, 0.0f, -20.0f},
		{0.0f, 1.0f, 0.0f},
		{0.3f, 0.0f},
		5.00f,
		5.0f * 5.0f,
	};
	t_sphere s3 = {
		{55.0f, 2.0f, -10.0f},
		{1.0f, 1.0f, 0.0f},
		{0.3f, 0.0f},
		5.00f,
		5.0f * 5.0f,
	};
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = s1;
	spheres[1] = s2;
	spheres[2] = s3;
	/***** END OF TEST SETUP *****/

	hittables.cylinders = cylinders;
	hittables.planes = planes;
	hittables.spheres = spheres;

	master.htbl = &hittables;
	master.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MINI RAY TRACER", true);
	master.mlx_img = mlx_new_image(master.mlx, img.image_width, img.image_height);
	if (!master.mlx_img || (mlx_image_to_window(master.mlx, master.mlx_img, 0, 0) < 0))
		exit(1);
	//mlx_key_hook(master.mlx, &check_events, &master);
	if (!mlx_loop_hook(master.mlx, &minirt, &master)) 	
		mlx_terminate(master.mlx);
	mlx_loop(master.mlx);
	mlx_terminate(master.mlx);
	
	return (0);
}
