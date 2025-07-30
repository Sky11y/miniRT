#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

inline static bool is_window_size_changed(mlx_t *mlx)
{
	static int32_t width = WIN_WIDTH;
	static int32_t height = WIN_HEIGHT;

	if (mlx->width != width || mlx->height != height)
	{
		width = mlx->width;
		height = mlx->height;
		return (true);
	}
	return (false);
}

inline static void	minirt(void *param)
{
	t_master *master = (t_master *)param;
	if (is_window_size_changed(master->mlx))
	{
		master->img = setup_image(master->img, master->mlx->width, master->mlx->height);
		master->cam = setup_camera(master->cam, master->img);
		mlx_resize_image(master->mlx_img, master->mlx->width, master->mlx->height);
	}
	render(master, master->mlx_img);
}

int main()
{
	t_master	master;
	t_camera	cam;
	t_image		img;
	t_lights	light;
	t_hittables	hittables;

	master.light = init_lights(&light);
	master.img = setup_image(&img, WIN_WIDTH, WIN_HEIGHT);
	master.cam = setup_camera(&cam, &img);
	
	/***** HERE IS THE TESTS FOR DIFFERENT HITTABLE OBJECTS *****/

	//TESTING THE SCHOOL SUBJECT EXAMPLE
	hittables.cylinder_count = 1;
	hittables.sphere_count = 1;
	hittables.plane_count = 2;

	t_cylinder c1 = {
		{15.0f, 0.0f, -10.6f},		//position
		{0.0f, 1.0f, 1.0f},	//orientation
		{0, 0, 0},			//base point -> initialised to zero and calculated later
		{10.0 / 255, 0.0f, 1.0f},		//color
		14.2 / 2.0f,				//radius 
		7.1f * 7.1f,		//radius squared
		21.42f,				//height
		0.5f,				//reflect (higher == more reflective)
		METAL,
	};
	t_cylinder c2 = {
		{-1.2, 0.0, 3},
		{0.2, 1.0, 0.6},
		{0, 0, 0},
		{1.0, 0, 0},
		0.5f,
		0.5f * 0.5f,
		0.5f,
		0.4f,
		METAL,
	};
	c1.axis_v = unit_vector(c1.axis_v);
	c1.base  = vv_sub(c1.center, vt_mul(c1.axis_v, c1.height / 2));
	c2.axis_v = unit_vector(c2.axis_v);
	c2.base  = vv_sub(c2.center, vt_mul(c2.axis_v, c2.height / 2));
	t_cylinder *cylinders = malloc(sizeof(t_cylinder) * hittables.cylinder_count);	
	cylinders[0] = c1;
	//cylinders[1] = c2;
	//
	t_plane p1 = {
		{0, -25.0f, 0.0f},		//position
		{0.0f, 1.0f, 0.0f},	//orientation
		{1.0f, 0.0f, 1.0f},		//color
		0.3,			//reflect
		METAL,
	};
	t_plane p2 = {
		{0, -2.1f, -50.0f},
		{0.0f, 0.0f, 1.0f},
		{0.6f, 0.6f, 0.85f},
		0.8,
		METAL,
	};
	p1.orientation = unit_vector(p1.orientation);
	p2.orientation = unit_vector(p2.orientation);
	t_plane	*planes = malloc(sizeof(t_plane) * hittables.plane_count);	
	planes[0] = p1;
	planes[1] = p2;

	t_sphere s1 = {
		{0.0f, 0.0f, -40.0f},	//position
		{0.0f, 1.0f, 1.0f},	//color
		20.0f,			//radius
		GLASS,
	};
	t_sphere s2 = {
		{0, -2.1f, 1.0f},
		{0, 1.0f, 0},
		0.90f,
		METAL
	};
	(void)s2;
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = s1;
	//spheres[1] = s2;
	/***** END OF TEST SETUP *****/

	hittables.cylinders = cylinders;
	hittables.planes = planes;
	hittables.spheres = spheres;

	master.htbl = &hittables;
	master.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MINI RAY TRACER", true);
	master.mlx_img = mlx_new_image(master.mlx, img.image_width, img.image_height);
	if (!master.mlx_img || (mlx_image_to_window(master.mlx, master.mlx_img, 0, 0) < 0))
		exit(1);
	mlx_key_hook(master.mlx, &check_events, &master);
	if (!mlx_loop_hook(master.mlx, &minirt, &master)) 	
		mlx_terminate(master.mlx);
	mlx_loop(master.mlx);
	
	return (0);
}
