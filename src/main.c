#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

FILE *infolog;

int main()
{
	t_image		img;
	t_camera	cam;
	t_hittables hittables;
	t_lights	light;

	infolog = fopen("log.md", "w+");
	if (infolog == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	
	init_lights(&light);
	init_image(&img);
	init_camera(&cam, &img);
	printf("P3\n%d %d\n255\n", img.image_width, img.image_height);
	fprintf(infolog, "width: %d, height: %d\n", img.image_width, img.image_height);
	
	
	/***** HERE IS THE TESTS FOR DIFFERENT HITTABLE OBJECTS *****/

	//TESTING THE SCHOOL SUBJECT EXAMPLE
	hittables.cylinder_count = 2;
	hittables.sphere_count = 2;
	hittables.plane_count = 2;

	//t_cylinder c1 = {{50.0, 0.0, 20.6}, {0, 0, 1.0}, {10, 0, 255 }, 14.2, 21.42};
	t_cylinder c1 = {
		{1.3, 0.0, 3},		//position
		{0.2, 1.0, -0.6},	//orientation
		{0, 0, 0},			//base point -> initialised to zero and calculated later
		{0.0, 0.0, 1},		//color
		0.5f,				//radius
		0.5f * 0.5f,		//radius squared
		0.2f,				//height
	};
	t_cylinder c2 = {
		{-1.2, 0.0, 3},		
		{0.2, 1.0, 0.6},	
		{0, 0, 0},			
		{1.0, 0, 0},		
		0.5f,				
		0.5f * 0.5f,		
		0.5f,				
	};
	t_cylinder c3 = {
		{0.0, 0.0, 1},		
		{0.0, 0.0, 1.0},	
		{0, 0, 0},			
		{1.0, 0, 0},		
		0.5f,				
		0.5f * 0.5f,		
		0.5f,				
	};
	c1.axis_v = unit_vector(c1.axis_v);
	c1.base  = vv_sub(c1.center, vt_mul(c1.axis_v, c1.height / 2));
	c2.axis_v = unit_vector(c2.axis_v);
	c2.base  = vv_sub(c2.center, vt_mul(c2.axis_v, c2.height / 2));
	c3.axis_v = unit_vector(c3.axis_v);
	c3.base  = vv_sub(c3.center, vt_mul(c3.axis_v, c3.height / 2));
	t_cylinder *cylinders = malloc(sizeof(t_cylinder) * hittables.cylinder_count);	
	cylinders[0] = c1;
	cylinders[1] = c2;
	//cylinders[2] = c3;
	//
	t_plane p1 = {
		{0, 0, 6},			//position
		{0.0, 0.0, 1.0},	//orientation
		{0.8, 0.8, 0.8},	//color
	};
	t_plane p2 = {
		{0, -1, 0},
		{0.0, 1.0, 0},
		{0.6, 0.6, 0.85},
	};
	p1.orientation = unit_vector(p1.orientation);
	p2.orientation = unit_vector(p2.orientation);
	t_plane	*planes = malloc(sizeof(t_plane) * hittables.plane_count);	
	planes[0] = p1;
	planes[1] = p2;

	//t_sphere s1 = {{0, 0, 20}, {255, 0, 0}, 20.0f};
	t_sphere s1 = {
		{0.0, 0.3, 3},	//position
		{1, 1, 0},		//color
		0.5f,			//radius
	};
	t_sphere s2 = {
		{0, -1, 1},
		{0, 1, 0},
		0.8f,
	};
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = s1;
	spheres[1] = s2;
	/***** END OF TEST SETUP *****/

	hittables.cylinders = cylinders;
	hittables.planes = planes;
	hittables.spheres = spheres;
	render(&hittables, &cam, &img, &light);
	
	fclose(infolog);
	return (0);
}
