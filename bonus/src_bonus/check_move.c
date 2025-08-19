#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

inline static bool	is_window_size_changed(mlx_t *mlx)
{
	static int32_t	width = WIN_WIDTH;
	static int32_t	height = WIN_HEIGHT;
	static int32_t	max_width;
	static int32_t	max_height;

	max_width = 0;
	max_height = 0;
	if (mlx->width == width && mlx->height == height)
		return (false);
	mlx_get_monitor_size(0, &max_width, &max_height);
	if (mlx->width > max_width)
		mlx->width = max_width;
	if (mlx->height > max_height)
		mlx->height = max_height;
	height = mlx->height;
	width = mlx->width;
	mlx_set_window_size(mlx, mlx->width, mlx->height);
	return (true);
}

inline static bool	is_camera_moved(t_camera *cam)
{
	static t_vec3f	prev_pos;
	static t_vec3f	prev_orientation;

	if (prev_pos.x == cam->center.x && prev_pos.y == cam->center.y
		&& prev_pos.z == cam->center.z
		&& prev_orientation.x == cam->orientation.x
		&& prev_orientation.y == cam->orientation.y
		&& prev_orientation.z == cam->orientation.z)
		return (false);
	prev_pos.x = cam->center.x;
	prev_pos.y = cam->center.y;
	prev_pos.z = cam->center.z;
	prev_orientation.x = cam->orientation.x;
	prev_orientation.y = cam->orientation.y;
	prev_orientation.z = cam->orientation.z;
	return (true);
}

void	check_changes(void *param)
{
	t_master	*m;
	bool		window_size_changed;

	m = (t_master *)param;
	window_size_changed = false;
	if (is_window_size_changed(m->mlx))
	{
		m->img = setup_image(m->img, m->mlx->width, m->mlx->height);
		mlx_resize_image(m->mlx_img, m->mlx->width, m->mlx->height);
		window_size_changed = true;
	}
	if (window_size_changed || is_camera_moved(m->cam))
	{
		m->cam = setup_camera(m->cam, m->img);
		m->renderer->rendr_done = false;
	}
}
