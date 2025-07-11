#include "mini_rt.h"
#include "scene_elements.h"

float	count_light(const t_vec3f normal, const t_vec3f hp,
		const t_lights *light)
{
	float			i;
	t_vec3f			light_dir;
	float			diffuse;

	i = light->ambient_brightness;
	light_dir = unit_vector(vv_sub(light->point_center, hp));
	diffuse = dot(normal, light_dir);
	if (diffuse > 0.0f)
		i += light->point_brightness * diffuse;
	return (i);
}
