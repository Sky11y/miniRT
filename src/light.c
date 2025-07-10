#include "mini_rt.h"
#include "scene_elements.h"

float	count_light(const t_vec3f normal, const t_vec3f hp,
		const t_lights *light)
{
	float			i;
	t_vec3f			light_to_hp;
	float			shadow;

	i = light->ambient_brightness;
	light_to_hp = vv_sub(light->point_center, hp);
	shadow = dot(normal, light_to_hp);
	if (shadow > 0)
		i += 0.7f * shadow / (v_length(normal) * v_length(light_to_hp));
	return (i);
}
