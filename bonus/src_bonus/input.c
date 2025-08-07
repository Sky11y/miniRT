#include "mini_rt.h"
#include "scene_elements.h"

void	input_keys(mlx_key_data_t kd, void *param)
{
	t_master			*m;

	m = (t_master *)param;
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(m->mlx);
}

void	check_keys(void *param)
{
	t_master	*m;
	static const float	cam_speed = 50.0f;
	float			delta_move;

	m = (t_master *)param;
	delta_move = cam_speed * (float)m->mlx->delta_time;
	if (mlx_is_key_down(m->mlx, MLX_KEY_W)) 
		m->cam->center = vv_add(m->cam->center,	vt_mul(m->cam->v, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->v, delta_move)); 
	else if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		m->cam->center = vv_add(m->cam->center,	vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_E))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->w, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_C))
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->w, delta_move));
	else
	{
		m->move = false;
		return ;
	}
	m->move = true;
}

/*inline bool	check_keys(t_master *m)
{
	static const float	cam_speed = 50.0f;
	const float			delta_move = cam_speed * (float)m->mlx->delta_time;

	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
	else if (mlx_is_key_down(m->mlx, MLX_KEY_W)) 
		m->cam->center = vv_add(m->cam->center,	vt_mul(m->cam->v, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->v, delta_move)); 
	else if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		m->cam->center = vv_add(m->cam->center,	vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_E))
		m->cam->center = vv_sub(m->cam->center,	vt_mul(m->cam->w, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_C))
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->w, delta_move));
	else
		return (false);
	return (true);
}*/
//pos[0], prev_pos[0], delta_pos[0] are x positions
//pos[1], prev_pos[1], delta_pos[1] are y positions
void	input_mouse(double xpos, double ypos, void *param)
{
	t_master		*m;
	static double	prev_pos[2];
	double			delta_pos[2];
	static bool		first_frame = true;
	float			delta_rotate;

	m = (t_master *)param;
	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		delta_rotate = 0.005f * (float)m->mlx->delta_time;
		if (first_frame)
		{
			prev_pos[0] = xpos;
			prev_pos[1] = ypos;
			first_frame = false;
		}
		delta_pos[0] = xpos - prev_pos[0];
		delta_pos[1] = ypos - prev_pos[1];
		m->cam->orientation.x -= delta_pos[0] * delta_rotate;
		m->cam->orientation.y += delta_pos[1] * delta_rotate;
		m->cam->orientation = unit_vector(m->cam->orientation);
		prev_pos[0] = xpos;
		prev_pos[1] = ypos;
		m->move = true;
		return ;
	}
	first_frame = true;
	m->move = false;
}

void	input_scroll(double xdelta, double ydelta, void *param)
{
	t_master		*m;
	float			delta_move;

	m = (t_master *)param;
	(void)xdelta;
	delta_move = 50.0f * (float)m->mlx->delta_time;
	if (ydelta < 0)
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->w, delta_move));
	else if (ydelta > 0)
		m->cam->center = vv_sub(m->cam->center, vt_mul(m->cam->w, delta_move));
	else
		m->move = false;
	m->move = true;
}
/*
//pos[0], prev_pos[0], delta_pos[0] are x positions
//pos[1], prev_pos[1], delta_pos[1] are y positions
bool	check_mouse(t_master *m)
{
	int32_t			pos[2];
	static int32_t	prev_pos[2];
	int32_t			delta_pos[2];
	static bool		first_frame = true;
	float			delta_rotate;

	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		delta_rotate = 0.005f * (float)m->mlx->delta_time;
		mlx_get_mouse_pos(m->mlx, &pos[0], &pos[1]);
		if (first_frame)
		{
			prev_pos[0] = pos[0];
			prev_pos[1] = pos[1];
			first_frame = false;
		}
		delta_pos[0] = pos[0] - prev_pos[0];
		delta_pos[1] = pos[1] - prev_pos[1];
		m->cam->orientation.x -= delta_pos[0] * delta_rotate;
		m->cam->orientation.y += delta_pos[1] * delta_rotate;
		m->cam->orientation = unit_vector(m->cam->orientation);
		prev_pos[0] = pos[0];
		prev_pos[1] = pos[1];
		return (true);
	}
	first_frame = true;
	return (false);
}*/
