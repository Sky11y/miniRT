#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

inline static bool	is_window_size_changed(mlx_t *mlx)
{
	static int32_t	width = WIN_WIDTH;
	static int32_t	height = WIN_HEIGHT;

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
	t_master	*m;

	m = (t_master *)param;
	if (is_window_size_changed(m->mlx))
	{
		m->img = setup_image(m->img, m->mlx->width, m->mlx->height);
		m->cam = setup_camera(m->cam, m->img);
		mlx_resize_image(m->mlx_img, m->mlx->width, m->mlx->height);
	}
	render(m, m->mlx_img);
}

static int	init_parsing(int argc, char *arg, t_parser *parser,
						t_hittables *htbls)
{
	if (argc != 2)
	{
		print_error("error: usage: ./miniRT [maps/mapname]");
		return (1);
	}
	ft_memset(parser, 0, sizeof(t_parser));
	ft_memset(htbls, 0, sizeof(t_hittables));
	parser->hittables = htbls;
	if (parse_file(arg, parser))
		return (1);
	if (init_shapes(arg, parser))
	{
		rt_cleanup(parser);
		return (1);
	}
	return (0);
}

static int	run_mlx(t_master *m, t_image *img)
{
	m->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MINI RAY TRACER", true);
	m->mlx_img = mlx_new_image(m->mlx, img->image_width, img->image_height);
	if (!m->mlx_img || (mlx_image_to_window(m->mlx, m->mlx_img, 0, 0) < 0))
		return (print_error("error: mlx error\n"));
	mlx_key_hook(m->mlx, &check_events, m);
	if (!mlx_loop_hook(m->mlx, &minirt, m))
		mlx_terminate(m->mlx);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	m;
	t_hittables	hittables;
	t_image		img;
	t_parser	parser;

	if (init_parsing(argc, argv[1], &parser, &hittables))
		return (1);
	m.light = parser.lights;
	m.img = setup_image(&img, WIN_WIDTH, WIN_HEIGHT);
	m.cam = parser.camera;
	m.cam = setup_camera(m.cam, &img);
	m.htbl = parser.hittables;
	if (run_mlx(&m, &img))
	{
		rt_cleanup(&parser);
		return (1);
	}
	rt_cleanup(&parser);
	return (0);
}
