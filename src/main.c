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

int main(int argc, char **argv)
{
	t_master	master;
	t_hittables	hittables;
	t_camera	*cam;
	t_image		img;
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
	cam = parser.camera;
	master.cam = setup_camera(cam, &img);
	master.htbl = parser.hittables;
	master.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MINI RAY TRACER", true);
	master.mlx_img = mlx_new_image(master.mlx, img.image_width, img.image_height);
	if (!master.mlx_img || (mlx_image_to_window(master.mlx, master.mlx_img, 0, 0) < 0))
		exit(1);
	mlx_key_hook(master.mlx, &check_events, &master);
	if (!mlx_loop_hook(master.mlx, &minirt, &master)) 	
		mlx_terminate(master.mlx);
	mlx_loop(master.mlx);
	rt_cleanup(&parser);
	return (0);
}
