#include "mini_rt.h"
#include "scene_elements.h"

void	input_keys(mlx_key_data_t kd, void *param)
{
	t_master	*m;

	m = (t_master *)param;
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(m->mlx);
}

void	check_keys(void *param)
{
	t_master			*m;
	static const float	cam_speed = 250.0f;
	float				delta_move;

	m = (t_master *)param;
	delta_move = cam_speed * m->mlx->delta_time;
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->v, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		m->cam->center = vv_sub(m->cam->center, vt_mul(m->cam->v, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		m->cam->center = vv_sub(m->cam->center, vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->u, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_E))
		m->cam->center = vv_sub(m->cam->center, vt_mul(m->cam->w, delta_move));
	else if (mlx_is_key_down(m->mlx, MLX_KEY_C))
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->w, delta_move));
}

static void	update_orientation(t_camera *cam, double *prev_pos, double xpos,
		double ypos)
{
	static const float	sensitivity = 0.0005f;
	static const float	max_pitch = M_PI * 0.5f - 0.01f;
	double				delta_pos[2];

	delta_pos[0] = xpos - prev_pos[0];
	delta_pos[1] = ypos - prev_pos[1];
	cam->yaw -= delta_pos[0] * sensitivity;
	cam->pitch += delta_pos[1] * sensitivity;
	if (cam->pitch > max_pitch)
		cam->pitch = max_pitch;
	if (cam->pitch < -max_pitch)
		cam->pitch = -max_pitch;
	cam->orientation.x = cosf(cam->pitch) * cosf(cam->yaw);
	cam->orientation.y = sinf(cam->pitch);
	cam->orientation.z = cosf(cam->pitch) * sin(cam->yaw);
	cam->orientation = unit_vector(cam->orientation);
}

//pos[0], prev_pos[0], delta_pos[0] are x positions
//pos[1], prev_pos[1], delta_pos[1] are y positions
void	input_mouse(double xpos, double ypos, void *param)
{
	t_master		*m;
	static double	prev_pos[2];
	static bool		first_frame = true;

	m = (t_master *)param;
	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (first_frame)
		{
			prev_pos[0] = xpos;
			prev_pos[1] = ypos;
			first_frame = false;
			return ;
		}
		update_orientation(m->cam, prev_pos, xpos, ypos);
		prev_pos[0] = xpos;
		prev_pos[1] = ypos;
	}
	else
		first_frame = true;
}

void	input_scroll(double xdelta, double ydelta, void *param)
{
	t_master	*m;
	float		delta_move;

	m = (t_master *)param;
	(void)xdelta;
	delta_move = 100.0f * (float)m->mlx->delta_time;
	if (ydelta < 0)
		m->cam->center = vv_add(m->cam->center, vt_mul(m->cam->w, delta_move));
	else if (ydelta > 0)
		m->cam->center = vv_sub(m->cam->center, vt_mul(m->cam->w, delta_move));
}
