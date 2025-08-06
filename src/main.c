#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

int main(int argc, char **argv)
{
	t_master	master;
	t_hittables	hittables;

	if (argc != 2)
	{
		ft_putstr_fd("error: usage: ./miniRT [maps/mapname]", 2);
		return (1);
	}
	ft_memset(&master, 0, sizeof(master));
	ft_memset(&hittables, 0, sizeof(hittables));
	master.hittables = &hittables;
	if (parse_file(argv[1], &master))
		return (1);
	if (init_shapes(argv[1], &master))
	{
		rt_cleanup(&master);
		return (1);
	}
	rt_cleanup(&master);
	return (0);
}
