#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

void	set_material(t_material *mat, float ref, float tran, float ior)
{
	mat->reflect = ref;
	mat->transparency = tran;
	mat->ior = ior;
}
