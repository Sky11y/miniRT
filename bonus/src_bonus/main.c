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

inline static bool is_camera_moved(t_camera *cam)
{
	static t_vec3f	prev_pos; 

	if (prev_pos.x == cam->center.x && prev_pos.y == cam->center.y
		&& prev_pos.z != cam->center.z)
		return (false);
	prev_pos.x = cam->center.x;
	prev_pos.y = cam->center.y;
	prev_pos.z = cam->center.z;
	return (true);
}

void	*render_sharp(void *param);

void	sharpen_image(t_master *m, t_renderer *r)
{
	static int frame = 0;

	int starting_row = THREAD_COUNT * THREAD_COUNT * frame;
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
		pthread_create(&r->threads[i], NULL, render_sharp, &r->args[i]);
		//handle errors
	}
	int count = 0;
	while (count < THREAD_COUNT)
	{
		if (pthread_join(r->threads[count++], NULL))
			exit(1);
	}
	if (frame * THREAD_COUNT * THREAD_COUNT > m->mlx->height)
		frame = 0;
	r->rendering = false;
}

void	*render_sharp(void *param)
{
	t_thread *thread = (t_thread *)param;
	const uint16_t	img_height = thread->height;
	const uint16_t	img_width = thread->width;
	t_vec3f			final_pixel_color;
	uint32_t		color;
	int				idx[2];

	idx[0] = thread->id;
	int i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(thread->htbl,
					thread->cam, idx, thread->light);
			color = get_color(final_pixel_color);
			thread->pixels[idx[0] * img_width + idx[1]] = color;
			idx[1] += 1;
		}
		memcpy(&thread->mlx_img->pixels[idx[0] * img_width * 4],
				&thread->pixels[idx[0] * img_width],
				sizeof(uint32_t) * img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}

void	check_changes(void *param)
{
	t_master	*m;
	bool		window_size_changed;

	m = (t_master *)param;
	window_size_changed = false;
	m->renderer->rendering = false;
	if (is_window_size_changed(m->mlx))
	{
		m->img = setup_image(m->img, m->mlx->width, m->mlx->height);
		m->renderer = setup_renderer(m->renderer, m->img);
		mlx_resize_image(m->mlx_img, m->mlx->width, m->mlx->height);
		window_size_changed = true;
	}
	if (window_size_changed || is_camera_moved(m->cam)) //m->move)
	{
		//last_change = mlx_get_time();
		m->cam = setup_camera(m->cam, m->img);
		m->renderer->rendering_done = false;
	}

}

static void	minirt(void *param)
{
	t_master	*m = (t_master *)param;
	t_renderer	*r = m->renderer;
	uint16_t	starting_row;
	static int	frame = 0;
	//static double	last_change;

	if (!r->rendering && !r->rendering_done)
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
	if (!r->rendering && r->rendering_done)
		sharpen_image(m, r);
	frame++;
	if (frame * THREAD_COUNT * THREAD_COUNT >= m->mlx->height)
	{
		frame = 0;
		//if (mlx_get_time() - last_change > m->mlx->delta_time * 10) {
		r->rendering_done = true;
		//	printf("I'm done with moving\n");
		//}
	}

//	printf("delta time %lf\n", m->mlx->delta_time);
}

/*
static void	print_values(t_parser master)
{
	float bright = master.lights->ambient_brightness;
	float r = master.lights->ambient_color.x;
	float g = master.lights->ambient_color.y;
	float b = master.lights->ambient_color.z;
	float tx = master.lights->ambient_tint.x;
	float ty = master.lights->ambient_tint.y;
	float tz = master.lights->ambient_tint.z;
	printf("A - brightness: %f - colors: %f, %f, %f ", bright, r, g, b);
	printf("- tint: %f %f %f\n", tx, ty, tz);

	float cx = master.camera->center.x;
	float cy = master.camera->center.y;
	float cz = master.camera->center.z;
	printf("C - center: %f %f %f ", cx, cy, cz);
	float ox = master.camera->orientation.x;
	float oy = master.camera->orientation.y;
	float oz = master.camera->orientation.z;
	float fov = master.camera->fov;
	printf("- orientation: %f %f %f - fov: %f\n", ox, oy, oz, fov);

	float lx = master.lights->point_center.x;
	float ly = master.lights->point_center.y;
	float lz = master.lights->point_center.z;
	float lr = master.lights->point_color.x;
	float lg = master.lights->point_color.y;
	float lb = master.lights->point_color.z;
	float lbright = master.lights->point_brightness;
	printf("L - center: %f %f %f ", lx, ly, lz);
	printf("- brightness: %f - colors: %f, %f, %f\n", lbright, lr, lg, lb);

	int	i = 0;
	while (i < master.hittables->plane_count)
	{
		float ppx = master.hittables->planes[i].pos.x;
		float ppy = master.hittables->planes[i].pos.y;
		float ppz = master.hittables->planes[i].pos.z;
		float pox = master.hittables->planes[i].orientation.x;
		float poy = master.hittables->planes[i].orientation.y;
		float poz = master.hittables->planes[i].orientation.z;
		float plr = master.hittables->planes[i].color.x;
		float plg = master.hittables->planes[i].color.y;
		float plb = master.hittables->planes[i].color.z;
		printf("pl[%d] - pos: %f %f %f ",i,  ppx, ppy, ppz);
		printf("- orientation: %f %f %f ", pox, poy, poz);
		printf("- color: %f %f %f\n", plr, plg, plb);
		i++;
	}

	i = 0;
	while (i < master.hittables->sphere_count)
	{
		float spx = master.hittables->spheres[i].center.x;
		float spy = master.hittables->spheres[i].center.y;
		float spz = master.hittables->spheres[i].center.z;
		float spr = master.hittables->spheres[i].color.x;
		float spg = master.hittables->spheres[i].color.y;
		float spb = master.hittables->spheres[i].color.z;
		float sprad = master.hittables->spheres[i].radius;
		printf("sp[%d] - pos: %f %f %f ",i,  spx, spy, spz);
		printf("- radius: %f ", sprad);
		printf("- color: %f %f %f\n", spr, spg, spb);
		i++;
	}

	i = 0;
	while (i < master.hittables->cylinder_count)
	{
		float cyx = master.hittables->cylinders[i].center.x;
		float cyy = master.hittables->cylinders[i].center.y;
		float cyz = master.hittables->cylinders[i].center.z;
		float cyaxx = master.hittables->cylinders[i].axis_v.x;
		float cyaxy = master.hittables->cylinders[i].axis_v.y;
		float cyaxz = master.hittables->cylinders[i].axis_v.z;
		float cyr = master.hittables->cylinders[i].color.x;
		float cyg = master.hittables->cylinders[i].color.y;
		float cyb = master.hittables->cylinders[i].color.z;
		float cyrad = master.hittables->cylinders[i].radius;
		float cyh = master.hittables->cylinders[i].height;
		float cyradsq = master.hittables->cylinders[i].radius_squared;
		printf("cy[%d] - pos: %f %f %f ",i,  cyx, cyy, cyz);
		printf("cy[%d] - axis_v: %f %f %f ",i,  cyaxx, cyaxy, cyaxz);
		printf("- radius: %f ", cyrad);
		printf("- height: %f ", cyh);
		printf("- radius squared: %f ", cyradsq);
		printf("- color: %f %f %f\n", cyr, cyg, cyb);
		i++;
	}
}
*/

int main(int argc, char **argv)
{
	t_master	master;
	t_image		img;
	t_renderer	r;
	t_hittables	hittables;
	t_parser	parser;

	if (argc != 2)
	{
		ft_putstr_fd("error: usage: ./miniRT [maps/mapname]", 2);
		return (1);
	}
	ft_memset(&parser, 0, sizeof(t_parser));
	ft_memset(&hittables, 0, sizeof(t_hittables));
	parser.hittables = &hittables;
	if (parse_file(argv[1], &parser))
		return (1);
	if (init_shapes(argv[1], &parser))
	{
		rt_cleanup(&parser);
		return (1);
	}
	master.light = parser.lights;
	master.img = setup_image(&img, WIN_WIDTH, WIN_HEIGHT);
	master.cam = parser.camera;
	master.cam = setup_camera(master.cam, &img);
	master.renderer = init_renderer(&r, &img);
	master.htbl = parser.hittables;
	//print_values(parser);
	//return (0);
	master.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MINI RAY TRACER", true);
	master.mlx_img = mlx_new_image(master.mlx, img.image_width, img.image_height);
	if (!master.mlx_img || (mlx_image_to_window(master.mlx, master.mlx_img, 0, 0) < 0))
		exit(1);
	mlx_key_hook(master.mlx, &input_keys, &master);
	if (!mlx_loop_hook(master.mlx, &check_keys, &master))
		mlx_terminate(master.mlx);
	mlx_cursor_hook(master.mlx, &input_mouse, &master);
	//if (!mlx_loop_hook(master.mlx, &check_mouse, &master))
	//	mlx_terminate(master.mlx);
	mlx_scroll_hook(master.mlx, &input_scroll, &master);
	if (!mlx_loop_hook(master.mlx, &check_changes, &master))
		mlx_terminate(master.mlx);
	if (!mlx_loop_hook(master.mlx, &minirt, &master)) 	
		mlx_terminate(master.mlx);
	mlx_loop(master.mlx);
	mlx_terminate(master.mlx);
	
	return (0);
}
