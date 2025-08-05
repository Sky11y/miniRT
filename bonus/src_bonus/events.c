#include "mini_rt.h"
#include "scene_elements.h"

inline bool	check_keys(t_master *m)
{
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
	else if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		m->cam->center.z -= 15.0f * (float)m->mlx->delta_time;
	else if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		m->cam->center.z += 15.0f * (float)m->mlx->delta_time;
	else if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		m->cam->center.x -= 15.0f * (float)m->mlx->delta_time;
	else if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		m->cam->center.x += 15.0f * (float)m->mlx->delta_time;
	else
		return (false);
	return (true);
}

//pos[0], prev_pos[0], delta_pos[0] are x positions
//pos[1], prev_pos[1], delta_pos[1] are y positions
bool	check_mouse(t_master *m)
{
	int32_t			pos[2];
	static int32_t	prev_pos[2];
	int32_t			delta_pos[2];
	static bool		first_frame = true;

	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(m->mlx, &pos[0], &pos[1]);
		if (first_frame)
		{
			prev_pos[0] = pos[0];
			prev_pos[1] = pos[1];
			first_frame = false;
		}
		delta_pos[0] = pos[0] - prev_pos[0];
		delta_pos[1] = pos[1] - prev_pos[1];
		m->cam->orientation.x -= delta_pos[0] * 0.0002f;
		m->cam->orientation.y += delta_pos[1] * 0.0002f;
		prev_pos[0] = pos[0];
		prev_pos[1] = pos[1];
		return (true);
	}
	else
		first_frame = true;
	return (false);
}
