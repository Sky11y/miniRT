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

