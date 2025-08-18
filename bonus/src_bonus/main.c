#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static void	minirt(void *param)
{
	t_master	*m;
	t_renderer	*r;
	static int	frame = 0;

	m = (t_master *)param;
	r = m->renderer;
	if (!r->rendr && !r->rendr_done && create_threads(m, r, frame, false))
		mlx_terminate(m->mlx);
	if (!r->rendr && r->rendr_done && create_threads(m, r, frame, true))
		mlx_terminate(m->mlx);
	if (r->rendr && join_threads(r))
		mlx_terminate(m->mlx);
	frame++;
	if (frame * THREAD_COUNT * THREAD_COUNT >= m->mlx->height)
	{
		frame = 0;
		r->rendr_done = true;
	}
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
	mlx_key_hook(m->mlx, &input_keys, m);
	if (!mlx_loop_hook(m->mlx, &check_keys, m))
		mlx_terminate(m->mlx);
	mlx_cursor_hook(m->mlx, &input_mouse, m);
	mlx_scroll_hook(m->mlx, &input_scroll, m);
	if (!mlx_loop_hook(m->mlx, &check_changes, m))
		mlx_terminate(m->mlx);
	if (!mlx_loop_hook(m->mlx, &minirt, m))
		mlx_terminate(m->mlx);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	master;
	t_image		img;
	t_renderer	r;
	t_hittables	hittables;
	t_parser	parser;

	if (init_parsing(argc, argv[1], &parser, &hittables))
		return (1);
	master.light = parser.lights;
	master.img = setup_image(&img, WIN_WIDTH, WIN_HEIGHT);
	master.cam = parser.camera;
	master.cam = setup_camera(master.cam, &img);
	master.renderer = init_renderer(&r);
	master.htbl = parser.hittables;
	if (run_mlx(&master, &img))
	{
		rt_cleanup(&parser);
		return (1);
	}
	rt_cleanup(&parser);
	return (0);
}
