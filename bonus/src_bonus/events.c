#include "mini_rt.h"
#include "scene_elements.h"

void	check_events(mlx_key_data_t keydata, void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(master->mlx);
	if (mlx_is_key_down(master->mlx, MLX_KEY_W))
		master->cam->center.z -= 0.5f;
	if (mlx_is_key_down(master->mlx, MLX_KEY_S))
		master->cam->center.z += 0.5f;
	if (mlx_is_key_down(master->mlx, MLX_KEY_A))
		master->cam->center.x -= 0.5f;
	if (mlx_is_key_down(master->mlx, MLX_KEY_D))
		master->cam->center.x += 0.5f;
}

void	check_mouse(t_master *m)
{
	int32_t			x;
	int32_t			y;
	static int32_t	prev_x;
	static int32_t	prev_y;
	int32_t			dx;
	int32_t			dy;
	static bool		first_frame = true;

	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(m->mlx, &x, &y);
		if (first_frame)
		{
			prev_x = x;
			prev_y = y;
			first_frame = false;
		}
		
		dx = x - prev_x;
		dy = y - prev_y;

		m->cam->orientation.x -= dx * 0.0002f;
		m->cam->orientation.y += dy * 0.0002f;
		m->cam->orientation = unit_vector(m->cam->orientation);

		prev_x = x;
		prev_y = y;
	}
	else
		first_frame = false;
}
